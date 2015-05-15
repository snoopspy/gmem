#include <map>
#include <dlfcn.h> // dlsym
#include <stdio.h> // fprintf
#include "gmemallocator.h"
#include "gmemmgr.h"

// ----------------------------------------------------------------------------
// GMemMgrLeakChecker
// ----------------------------------------------------------------------------
class GMemMgrLeakChecker {
public:
  struct Item {
    size_t size;
    char* file;
    int line;
  };
  typedef std::map<void*, Item, std::less<void*>, GMemAllocator<std::pair<const void*,Item> > > Items;
  Items items_;

public:
  void clear() {
    items_.clear();
  }

  void check() {
    if (items_.size() > 0) {
      fprintf(stderr, "******************************************************************************\n");
      for (Items::iterator it = items_.begin(); it != items_.end(); it++) {
        void* ptr = it->first;
        Item& item = it->second;
        fprintf(stderr, "memory leak %p(%d bytes) %s:%d\n", ptr, (int)item.size, item.file, item.line);
      }
      fprintf(stderr, "******************************************************************************\n");
    }
  }

  bool exists(void* ptr) {
    Items::iterator it = items_.find(ptr);
    return it != items_.end();
  }

  void add(void* ptr, size_t size, char* file, int line) {
    Item item;
    item.size = size;
    item.file = (char*)file;
    item.line = line;
    items_[ptr] = item;
  }

  void del(void* ptr) {
    Items::iterator it = items_.find(ptr);
    if (it == items_.end()) return;
    items_.erase(it);
  }
};

// ----------------------------------------------------------------------------
// GMemMgrImpl
// ----------------------------------------------------------------------------
class GMemMgrImpl : public GMemMgr {
public:
  GMemMgrImpl() {
  }
  virtual ~GMemMgrImpl() {

  }
  bool start() {
    if (active_) return false;
    leakChecker_.clear();
    oldMalloc_ = (void*(*)(size_t))dlsym(RTLD_NEXT, "malloc");
    if (oldMalloc_ == nullptr) {
      fprintf(stderr, "dlsym('malloc') return nullptr dlerror=%s\n", dlerror());
      goto _fail;
    }
    oldCalloc_ = (void*(*)(size_t, size_t))dlsym(RTLD_NEXT, "calloc");
    if (oldCalloc_ == nullptr) {
      fprintf(stderr, "dlsym('calloc') return nullptr dlerror=%s\n", dlerror());
      goto _fail;
    }
    oldRealloc_ = (void*(*)(void*, size_t))dlsym(RTLD_NEXT, "realloc");
    if (oldRealloc_ == nullptr) {
      fprintf(stderr, "dlsym('realloc') return nullptr dlerror=%s\n", dlerror());
      goto _fail;
    }
    oldFree_ = (void(*)(void*))dlsym(RTLD_NEXT, "free");
    if (oldFree_ == nullptr) {
      fprintf(stderr, "dlsym('malloc') return nullptr dlerror=%s\n", dlerror());
      goto _fail;
    }
    active_ = true;
    return true;

  _fail:
    oldMalloc_ = nullptr;
    oldCalloc_ = nullptr;
    oldRealloc_ = nullptr;
    oldFree_ = nullptr;
    return false;
  }

  bool stop(bool leakCheck) {
    if (!active_) return false;
    if (leakCheck) leakChecker_.check();
    leakChecker_.clear();
    active_ = false;
    return true;
  }

  bool restart() {
    bool res = true;
    if (!start()) res = false;
    if (!stop(false)) res = false;
    return res;
  }

public:
  void* malloc(size_t size, const char* file, const int line) {
    if (!active_ || oldMalloc_ == nullptr) return nullptr;
    void* ptr = oldMalloc_(size);
    if (ptr == nullptr) {
      fprintf(stderr, "oldMalloc_ return nullptr");
      return nullptr;
    }
    printf("GMemMgr::malloc (%p) %zu\n", ptr, size);

    if (leakChecker_.exists(ptr)) {
      fprintf(stderr, "ptr(%p) is already added size=%d file=%s line=%d\n", ptr, (int)size, file, line);
      return nullptr;
    }
    leakChecker_.add(ptr, size, (char*)file, line);
    return ptr;
  }

  void* calloc(size_t nmemb, size_t size, const char* file, const int line) {
    (void)nmemb;
    (void)size;
    (void)file;
    (void)line;
    return nullptr; // gilgil temp 2015.05.14
  }

  void* realloc(void* ptr, size_t size, const char* file, const int line) {
    (void)ptr;
    (void)size;
    (void)file;
    (void)line;
    return nullptr; // gilgil temp 2015.05.14
  }

  void free(void* ptr) {
    if (ptr == NULL) {
      fprintf(stderr, "ptr is null\n");
      return;
    }
    printf("GMemMgr::free   (%p)\n", ptr);
    leakChecker_.del(ptr);
  }

protected:
  bool active_ = false;
  GMemMgrLeakChecker leakChecker_;
  void* (*oldMalloc_)(size_t size) = nullptr;
  void* (*oldCalloc_)(size_t nmemb, size_t size) = nullptr;
  void* (*oldRealloc_)(void *ptr, size_t size) = nullptr;
  void (*oldFree_)(void* ptr) = nullptr;

};

// ----------------------------------------------------------------------------
// GMemMgr
// ----------------------------------------------------------------------------
GMemMgr::GMemMgr() {
  start();
}

GMemMgr::~GMemMgr() {
  stop();
}

bool GMemMgr::start() {
  GMemMgrImpl* impl = (GMemMgrImpl*)this;
  return impl->start();
}

bool GMemMgr::stop(bool leakCheck) {
  GMemMgrImpl* impl = (GMemMgrImpl*)this;
  return impl->stop(leakCheck);
}

bool GMemMgr::restart() {
  GMemMgrImpl* impl = (GMemMgrImpl*)this;
  return impl->restart();
}

void* GMemMgr::malloc(size_t size, const char* file, const int line) {
  GMemMgrImpl* impl = (GMemMgrImpl*)this;
  return impl->malloc(size, file, line);
}

void* GMemMgr::calloc(size_t nmemb, size_t size, const char* file, const int line) {
  GMemMgrImpl* impl = (GMemMgrImpl*)this;
  return impl->calloc(nmemb, size, file, line);
}

void* GMemMgr::realloc(void *ptr, size_t size, const char* file, const int line) {
  GMemMgrImpl* impl = (GMemMgrImpl*)this;
  return impl->realloc(ptr, size, file, line);
}

void GMemMgr::free(void* ptr) {
  GMemMgrImpl* impl = (GMemMgrImpl*)this;
  return impl->free(ptr);
}

GMemMgr& GMemMgr::instance() {
  static GMemMgr instance;
  return instance;
}

// ----------------------------------------------------------------------------
// override function
// ----------------------------------------------------------------------------
void *malloc(size_t size) __THROW {
  return GMemMgr::instance().malloc(size, nullptr, 0);
}

void free(void* ptr) __THROW {
  return GMemMgr::instance().free(ptr);
}

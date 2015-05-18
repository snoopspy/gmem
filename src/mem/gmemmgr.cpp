#include <cstdio> // fprintf
#include <unordered_map>
#include "gmemallocator.h"
#include "gmemhook.h"
#include "gmemmgr.h"

// ----------------------------------------------------------------------------
// GMemLeak
// ----------------------------------------------------------------------------
class GMemLeak {
public:
  struct Item {
    size_t size;
    char* file;
    int line;
  };
  typedef std::unordered_map<void*/*ptr*/, Item,
    std::hash<void*>,
    std::equal_to<void*>,
    GMemAllocator<std::pair<const void*,Item>>> Items;
  Items items_;

public:
  GMemLeak() {
    clear();
  }

  virtual ~GMemLeak() {
    check();
    clear();
  }

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
      items_.clear();
    }
  }

  bool exists(void* ptr) {
    Items::iterator it = items_.find(ptr);
    return it != items_.end();
  }

  void add(void* ptr, size_t size, const char* file, const int line) {
    if (items_.find(ptr) != items_.end()) {
      fprintf(stderr, "******************************************************************************\n");
      fprintf(stderr, "already exist ptr(%p) file=%s line=%d\n", ptr, file, line);
      fprintf(stderr, "******************************************************************************\n");
      return;
    }
    Item item;
    item.size = size;
    item.file = (char*)file;
    item.line = line;
    items_[ptr] = item;
  }

  void del(void* ptr, const char* file, const int line) {
    Items::iterator it = items_.find(ptr);
    if (it == items_.end()) {
      fprintf(stderr, "******************************************************************************\n");
      fprintf(stderr, "can not find ptr(%p) file=%s line=%d\n", ptr, file, line);
      fprintf(stderr, "******************************************************************************\n");
      return;
    }
    items_.erase(it);
  }

  static GMemLeak& instance() {
    static GMemLeak _memLeakImpl;
    return _memLeakImpl;
  }
};

// ----------------------------------------------------------------------------
// GMemMgrImpl
// ----------------------------------------------------------------------------
class GMemMgrImpl {
protected:
  GMemLeak memLeak_;

public:
  GMemMgrImpl() {
    GMemHook::instance().hook(_malloc, _free, _calloc, _realloc);
    start();
  }

  virtual ~GMemMgrImpl() {
    stop();
  }

  void start() {
    memLeak_.clear();
  }

  void stop() {
    memLeak_.check();
    memLeak_.clear();
  }

protected:
  static void* _malloc(size_t size) {
    return instance().malloc(size, nullptr, 0);
  }

  static void _free(void* ptr) {
    return instance().free(ptr, nullptr, 0);
  }

  static void* _calloc(size_t nmemb, size_t size) {
    return instance().calloc(nmemb, size, nullptr, 0);
  }

  static void* _realloc(void* ptr, size_t size) {
    return instance().realloc(ptr, size, nullptr, 0);
  }

public:
  void* malloc(size_t size, const char* file, const int line) {
    void* res = GMemHook::instance().orgMallocFunc_(size);
    memLeak_.add(res, size, file, line);
    return res;
  }

  void free(void* ptr, const char* file, const int line) {
    GMemHook::instance().orgFreeFunc_(ptr);
    memLeak_.del(ptr, file, line);
  }

  void* calloc(size_t nmemb, size_t size, const char* file, const int line) {
    void* res = GMemHook::instance().orgCallocFunc_(nmemb, size);
    memLeak_.add(res, size, file, line);
    return res;
  }

  void* realloc(void* ptr, size_t size, const char* file, const int line) {
    void* res = GMemHook::instance().orgReallocFunc_(ptr, size);
    memLeak_.del(ptr, file, line);
    memLeak_.add(res, size, file, line);
    return res;
  }

  static GMemMgrImpl& instance() {
    static GMemMgrImpl _memMgrImpl;
    return _memMgrImpl;
  }
};

// ----------------------------------------------------------------------------
// GMemMgr
// ----------------------------------------------------------------------------
void GMemMgr::start() {
  GMemMgrImpl::instance().start();
}

void GMemMgr::stop() {
  GMemMgrImpl::instance().stop();
}

void* GMemMgr::malloc(size_t size, const char* file, const int line) {
  return GMemMgrImpl::instance().malloc(size, file, line);
}

void GMemMgr::free(void* ptr, const char* file, const int line) {
  return GMemMgrImpl::instance().free(ptr, file, line);
}

void* GMemMgr::calloc(size_t nmemb, size_t size, const char* file, const int line) {
  return GMemMgrImpl::instance().calloc(nmemb, size, file, line);
}

void* GMemMgr::realloc(void* ptr, size_t size, const char* file, const int line) {
  return GMemMgrImpl::instance().realloc(ptr, size, file, line);
}

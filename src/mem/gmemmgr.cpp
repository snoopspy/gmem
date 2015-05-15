#include <stdio.h> // fprintf
#include "gmemallocator.h"
#include "gmemmgr.h"

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

    leakChecker_.clear();


  }

  bool stop(bool leakCheck) {
    if (leakCheck) leakChecker_.check();
    leakChecker_.clear();
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

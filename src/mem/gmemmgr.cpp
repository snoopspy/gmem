#include <cstdio> // fprintf
#include "gmemleak.h"
#include "gmemhook.h"
#include "gmemmgr.h"

// ----------------------------------------------------------------------------
// GMemMgrImpl
// ----------------------------------------------------------------------------
class GMemMgrImpl : public GMemMgr {
public:
  GMemMgrImpl() {
    start();
  }

  virtual ~GMemMgrImpl() {
    stop();
  }

  void start() {
    GMemLeak::clear();
  }

  void stop() {
    GMemLeak::check();
    GMemLeak::clear();
  }

public:
  void* malloc(size_t size, const char* file, const int line) {
    void* res = GMemHook::instance().orgMallocFunc_(size);
    GMemLeak::add(res, size, file, line);
    return res;
  }

  void free(void* ptr, const char* file, const int line) {
    GMemHook::instance().orgFreeFunc_(ptr);
    GMemLeak::del(ptr, file, line);
  }

  void* calloc(size_t nmemb, size_t size, const char* file, const int line) {
    void* res = GMemHook::instance().orgCallocFunc_(nmemb, size);
    GMemLeak::add(res, size, file, line);
    return res;
  }

  void* realloc(void* ptr, size_t size, const char* file, const int line) {
    void* res = GMemHook::instance().orgReallocFunc_(ptr, size);
    GMemLeak::add(res, size, file, line);
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

#include <dlfcn.h>  // dlsym
#include <stdio.h>  // fprintf
#include "gmemmgr.h"

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
  if (active_) return false;
  items_.clear();
  oldMalloc_ = (void*(*)(size_t))dlsym(RTLD_NEXT, "malloc");
  if (oldMalloc_ == nullptr) {
    fprintf(stderr, "dlsym('malloc') return nullptr dlerror=%s\n", dlerror());
    oldFree_ = nullptr;
    return false;
  }
  oldFree_ = (void(*)(void*))dlsym(RTLD_NEXT, "free");
  if (oldFree_ == nullptr) {
    fprintf(stderr, "dlsym('malloc') return nullptr dlerror=%s\n", dlerror());
    return false;
  }
  active_ = true;
  return true;
}

bool GMemMgr::stop(bool leakCheck) {
  if (!active_) return false;
  if (leakCheck && items_.size() > 0) {
    fprintf(stderr, "******************************************************************************\n");
    for (Items::iterator it = items_.begin(); it != items_.end(); it++) {
      void* ptr = it->first;
      Item& item = it->second;
      fprintf(stderr, "memory leak %p(%d bytes) %s:%d\n", ptr, (int)item.size, item.file, item.line);
    }
    fprintf(stderr, "******************************************************************************\n");
  }
  items_.clear();
  active_ = false;
  return true;
}

void* GMemMgr::malloc(size_t size, const char* file, const int line) {
  void* ptr = oldMalloc_(size);
  if (ptr == nullptr) {
    fprintf(stderr, "oldMalloc_ return nullptr");
    return nullptr;
  }
  printf("GMemMgr::malloc (%p) %zu\n", ptr, size);
  Items::iterator it = items_.find(ptr);
  if (it != items_.end()) {
    fprintf(stderr, "ptr(%p) is already added size=%d file=%s line=%d\n", ptr, (int)size, file, line);
    return NULL;
  }
  // ----- gilgil temp 2015.05.14 -----
  /*
  Item item;
  item.size = size;
  item.file = (char*)file;
  item.line = line;
  items_[ptr] = item;
  */
  // ----------------------------------
  return ptr;
}

void* GMemMgr::calloc(size_t nmemb, size_t size, const char* file, const int line) {
  (void)nmemb;
  (void)size;
  (void)file;
  (void)line;
  return nullptr; // gilgil temp 2015.05.14
}

void* GMemMgr::realloc(void *ptr, size_t size, const char* file, const int line) {
  (void)ptr;
  (void)size;
  (void)file;
  (void)line;
  return nullptr; // gilgil temp 2015.05.14
}

void GMemMgr::free(void* ptr) {
  if (ptr == NULL) {
    fprintf(stderr, "ptr is null\n");
    return;
  }
  printf("GMemMgr::free   (%p)\n", ptr);
  Items::iterator it = items_.find(ptr);
  if (it == items_.end()) return;
  items_.erase(it);
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

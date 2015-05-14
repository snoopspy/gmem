#include <stdio.h>  // printf
#include <stdlib.h> // malloc

#include "gmemfunc.h"
#include "gmemmgr.h"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-value"
#endif // __GNUC__

#define _debug

// ----------------------------------------------------------------------------
// control functions
// ----------------------------------------------------------------------------
void gmem_start(void) {
  GMemMgr::instance().start();
}

void gmem_stop(void) {
  GMemMgr::instance().stop();
}

// ----------------------------------------------------------------------------
// replace functions for c
// ----------------------------------------------------------------------------
void* gmem_malloc(size_t size, const char* file, const int line) {
  _debug("gmem_malloc(%d, %s, %d)\n", (int)size, file, line);
  void* res = GMemMgr::instance().malloc(size, file, line);
  return res;
}

void* gmem_calloc(size_t nmemb, size_t size, const char* file, const int line) {
  _debug("gmem_calloc(%d, %d, %s, %d)\n", (int)nmemb, (int)size, file, line);
  void* res = GMemMgr::instance().calloc(nmemb, size, file, line);
  return res;
}

void* gmem_realloc(void *ptr, size_t size, const char* file, const int line) {
  _debug("gmem_realloc(%p, %d, %s, %d)\n", ptr, (int)size, file, line);
  void* res = GMemMgr::instance().realloc(ptr, size, file, line);
  return res;
}

void gmem_free(void *ptr, const char* file, const int line) {
  _debug("gmem_free(%p, %s, %d)\n", ptr, file, line);
  GMemMgr::instance().free(ptr);
  free(ptr);
}

// ----------------------------------------------------------------------------
// replace operators for cpp
// ----------------------------------------------------------------------------
void* operator new(size_t size, const char* file, const int line) throw(std::bad_alloc) {
    _debug("new(%d, %s, %d)\n", (int)size, file, line);
    void* res = GMemMgr::instance().malloc(size, file, line);
    return res;
}

void* operator new[](size_t size, const char* file, const int line) throw(std::bad_alloc) {
    _debug("new[](%d, %s, %d)\n", (int)size, file, line);
    void* res = GMemMgr::instance().malloc(size, file, line);
    return res;
}

void operator delete(void* ptr) throw() {
    _debug("delete(%p)\n", ptr);
    GMemMgr::instance().free(ptr);
    free(ptr);
}

void operator delete[](void* ptr) throw() {
    _debug("delete[](%p)\n", ptr);
    GMemMgr::instance().free(ptr);
    free(ptr);
}

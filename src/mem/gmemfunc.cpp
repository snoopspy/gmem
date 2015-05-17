#include <stdio.h>  // printf
#include <stdlib.h> // malloc
#include "gmemfunc.h"
#include "gmemmgr.h"

// ----- gilgil temp 2015.05.17 -----
/*
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-value"
#endif // __GNUC__
*/
// ----------------------------------

#define _debug

// ----------------------------------------------------------------------------
// control functions
// ----------------------------------------------------------------------------
void gmem_start(void) {
  GMemMgr::start();
}

void gmem_stop(void) {
  GMemMgr::stop();
}

// ----------------------------------------------------------------------------
// replace functions for c
// ----------------------------------------------------------------------------
void* gmem_malloc(size_t size, const char* file, const int line) {
  return GMemMgr::malloc(size, file, line);
}

void gmem_free(void *ptr, const char* file, const int line) {
  return GMemMgr::free(ptr, file, line);
}

void* gmem_calloc(size_t nmemb, size_t size, const char* file, const int line) {
  return GMemMgr::calloc(nmemb, size, file, line);
}

void* gmem_realloc(void *ptr, size_t size, const char* file, const int line) {
  return GMemMgr::realloc(ptr, size, file, line);
}

// ----------------------------------------------------------------------------
// replace operators for cpp
// ----------------------------------------------------------------------------
void* operator new(size_t size, const char* file, const int line) throw(std::bad_alloc) {
  return GMemMgr::malloc(size, file, line);
}

void* operator new[](size_t size, const char* file, const int line) throw(std::bad_alloc) {
  return GMemMgr::malloc(size, file, line);
}

// ----------------------------------------------------------------------------
// global operators for cpp
// ----------------------------------------------------------------------------
void* operator new(size_t size) throw (std::bad_alloc) {
  return GMemMgr::malloc(size, nullptr, 0);
}

void* operator new[](size_t size) throw (std::bad_alloc) {
  return GMemMgr::malloc(size, nullptr, 0);
}

void operator delete(void* ptr) throw() {
  GMemMgr::free(ptr, nullptr, 0);
}

void operator delete[](void* ptr) throw() {
  GMemMgr::free(ptr, nullptr, 0);
}

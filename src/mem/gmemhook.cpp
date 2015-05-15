#include <assert.h>
#include <dlfcn.h> // dlsym
#include <stdio.h>
#include <stdlib.h>
#include "gmemhook.h"

// ----------------------------------------------------------------------------
// GMemHook
// ----------------------------------------------------------------------------
GMemHook::GMemHook() {
  orgMallocFunc_ = nowMallocFunc_ = (MallocFunc)dlsym(RTLD_NEXT, "malloc");
  if (orgMallocFunc_ == nullptr) {
    fprintf(stderr, "dlsym('malloc') return nullptr dlerror=%s\n", dlerror());
    goto _fail;
  }
  orgCallocFunc_ = nowCallocFunc_ = (CallocFunc)dlsym(RTLD_NEXT, "calloc");
  if (orgCallocFunc_ == nullptr) {
    fprintf(stderr, "dlsym('calloc') return nullptr dlerror=%s\n", dlerror());
    goto _fail;
  }
  orgReallocFunc_ = nowReallocFunc_ = (ReallocFunc)dlsym(RTLD_NEXT, "realloc");
  if (orgReallocFunc_ == nullptr) {
    fprintf(stderr, "dlsym('realloc') return nullptr dlerror=%s\n", dlerror());
    goto _fail;
  }
  orgFreeFunc_ = nowFreeFunc_ = (void(*)(void*))dlsym(RTLD_NEXT, "free");
  if (orgFreeFunc_ == nullptr) {
    fprintf(stderr, "dlsym('malloc') return nullptr dlerror=%s\n", dlerror());
    goto _fail;
  }
  return;
_fail:
  abort();
}

GMemHook::~GMemHook() {
  unhook();
}

void GMemHook::hook(
  MallocFunc mallocFunc,
  CallocFunc callocFunc,
  ReallocFunc reallocFunc,
  FreeFunc freeFunc) {
  nowMallocFunc_ = mallocFunc == nullptr ? orgMallocFunc_ : mallocFunc;
  nowCallocFunc_ = callocFunc == nullptr ? orgCallocFunc_ : callocFunc;
  nowReallocFunc_ = reallocFunc == nullptr ? orgReallocFunc_ : reallocFunc;
  nowFreeFunc_ = freeFunc == nullptr ? orgFreeFunc_ : freeFunc;
}

void GMemHook::unhook() {
  hook(nullptr, nullptr, nullptr, nullptr);
}

void* GMemHook::malloc(size_t size) {
  assert(nowMallocFunc_ != nullptr);
  return nowMallocFunc_(size);
}

void* GMemHook::calloc(size_t nmemb, size_t size) {
  assert(nowCallocFunc_ != nullptr);
  return nowCallocFunc_(nmemb, size);
}

void* GMemHook::realloc(void* ptr, size_t size) {
  assert(nowReallocFunc_ != nullptr);
  return nowReallocFunc_(ptr, size);
}

void GMemHook::free(void* ptr){
  assert(nowFreeFunc_ != nullptr);
  return nowFreeFunc_(ptr);
}

GMemHook& GMemHook::instance() {
  static GMemHook _instance;
  return _instance;
}

// ----------------------------------------------------------------------------
// override function
// ----------------------------------------------------------------------------
void *malloc(size_t size) __THROW {
  return GMemHook::instance().malloc(size);
}

void* calloc(size_t nmemb, size_t size) __THROW {
  return GMemHook::instance().calloc(nmemb, size);
}

void* realloc(void* ptr, size_t size) __THROW {
  return GMemHook::instance().realloc(ptr, size);
}

void free(void* ptr) __THROW {
  return GMemHook::instance().free(ptr);
}

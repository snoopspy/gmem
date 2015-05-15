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
  orgFreeFunc_ = nowFreeFunc_ = (FreeFunc)dlsym(RTLD_NEXT, "free");
  if (orgFreeFunc_ == nullptr) {
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
  return;
_fail:
  abort();
}

GMemHook::~GMemHook() {
  unhook();
}

void GMemHook::hook(
  MallocFunc mallocFunc,
  FreeFunc freeFunc,
  CallocFunc callocFunc,
  ReallocFunc reallocFunc) {
  nowMallocFunc_ = mallocFunc == nullptr ? orgMallocFunc_ : mallocFunc;
  nowFreeFunc_ = freeFunc == nullptr ? orgFreeFunc_ : freeFunc;
  nowCallocFunc_ = callocFunc == nullptr ? orgCallocFunc_ : callocFunc;
  nowReallocFunc_ = reallocFunc == nullptr ? orgReallocFunc_ : reallocFunc;
}

void GMemHook::unhook() {
  hook(nullptr, nullptr, nullptr, nullptr);
}

GMemHook& GMemHook::instance() {
  static GMemHook _instance;
  return _instance;
}

// ----------------------------------------------------------------------------
// override functions
// ----------------------------------------------------------------------------
void *malloc(size_t size) {
  assert(GMemHook::instance().nowMallocFunc_ != nullptr);
  return GMemHook::instance().nowMallocFunc_(size);
}

void* calloc(size_t nmemb, size_t size) {
  assert(GMemHook::instance().nowCallocFunc_ != nullptr);
  return GMemHook::instance().nowCallocFunc_(nmemb, size);
}

void* realloc(void* ptr, size_t size) {
  assert(GMemHook::instance().nowReallocFunc_ != nullptr);
  return GMemHook::instance().nowReallocFunc_(ptr, size);
}

void free(void* ptr) {
  assert(GMemHook::instance().nowFreeFunc_ != nullptr);
  return GMemHook::instance().nowFreeFunc_(ptr);
}

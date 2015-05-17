#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <dlfcn.h> // dlsym
#include "gmemhook.h"

// ----------------------------------------------------------------------------
// GMemHook
// ----------------------------------------------------------------------------
GMemHook::GMemHook() {
  orgMallocFunc_ = (MallocFunc)dlsym(RTLD_NEXT, "malloc");
  if (orgMallocFunc_ == nullptr) {
    fprintf(stderr, "dlsym('malloc') return nullptr dlerror=%s\n", dlerror());
    goto _fail;
  }
  orgFreeFunc_ = (FreeFunc)dlsym(RTLD_NEXT, "free");
  if (orgFreeFunc_ == nullptr) {
    fprintf(stderr, "dlsym('malloc') return nullptr dlerror=%s\n", dlerror());
    goto _fail;
  }
  orgCallocFunc_ = (CallocFunc)dlsym(RTLD_NEXT, "calloc");
  if (orgCallocFunc_ == nullptr) {
    fprintf(stderr, "dlsym('calloc') return nullptr dlerror=%s\n", dlerror());
    goto _fail;
  }
  orgReallocFunc_ = (ReallocFunc)dlsym(RTLD_NEXT, "realloc");
  if (orgReallocFunc_ == nullptr) {
    fprintf(stderr, "dlsym('realloc') return nullptr dlerror=%s\n", dlerror());
    goto _fail;
  }
  return;
_fail:
  abort();
}

GMemHook::~GMemHook() {
}

GMemHook& GMemHook::instance() {
  static GMemHook _instance;
  return _instance;
}

// ----------------------------------------------------------------------------
// override functions
// ----------------------------------------------------------------------------

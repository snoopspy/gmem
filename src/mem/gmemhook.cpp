#include <dlfcn.h> // dlsym
#include <stdio.h>
#include "gmemhook.h"

// ----------------------------------------------------------------------------
// GMemHook
// ----------------------------------------------------------------------------
GMemHook::GMemHook() {
  hook();
}

GMemHook::~GMemHook() {
  unhook();
}

bool GMemHook::hook() {
  if (active_) return false;

  malloc_ = (void*(*)(size_t))dlsym(RTLD_NEXT, "malloc");
  if (malloc_ == nullptr) {
    fprintf(stderr, "dlsym('malloc') return nullptr dlerror=%s\n", dlerror());
    goto _fail;
  }
  calloc_ = (void*(*)(size_t, size_t))dlsym(RTLD_NEXT, "calloc");
  if (calloc_ == nullptr) {
    fprintf(stderr, "dlsym('calloc') return nullptr dlerror=%s\n", dlerror());
    goto _fail;
  }
  realloc_ = (void*(*)(void*, size_t))dlsym(RTLD_NEXT, "realloc");
  if (realloc_ == nullptr) {
    fprintf(stderr, "dlsym('realloc') return nullptr dlerror=%s\n", dlerror());
    goto _fail;
  }
  free_ = (void(*)(void*))dlsym(RTLD_NEXT, "free");
  if (free_ == nullptr) {
    fprintf(stderr, "dlsym('malloc') return nullptr dlerror=%s\n", dlerror());
    goto _fail;
  }
  active_ = true;
  return true;

_fail:
  malloc_ = nullptr;
  calloc_ = nullptr;
  realloc_ = nullptr;
  free_ = nullptr;
  return false;
}

bool GMemHook::unhook() {
  if (!active_) return false;
  active_ = false;
  return true;
}

GMemHook& GMemHook::instance() {
  static GMemHook _instance;
  return _instance;
}

// ----------------------------------------------------------------------------
//
// G Library
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#pragma once

#include <cstddef> // for size_t

// ----------------------------------------------------------------------------
// GMemHook
// ----------------------------------------------------------------------------
class GMemHook {
protected:
  GMemHook();
  virtual ~GMemHook();

public:
  typedef void* (*MallocFunc) (size_t size);
  typedef void* (*CallocFunc) (size_t nmemb, size_t size);
  typedef void* (*ReallocFunc)(void* ptr,    size_t size);
  typedef void  (*FreeFunc)   (void* ptr);

  MallocFunc  orgMallocFunc_  = nullptr;
  CallocFunc  orgCallocFunc_  = nullptr;
  ReallocFunc orgReallocFunc_ = nullptr;
  FreeFunc    orgFreeFunc_    = nullptr;

  MallocFunc  nowMallocFunc_  = nullptr;
  CallocFunc  nowCallocFunc_  = nullptr;
  ReallocFunc nowReallocFunc_ = nullptr;
  FreeFunc    nowFreeFunc_    = nullptr;

public:
  void hook(
    MallocFunc  mallocFunc  = nullptr,
    CallocFunc  callocFunc  = nullptr,
    ReallocFunc reallocFunc = nullptr,
    FreeFunc    freeFunc    = nullptr);
  void unhook();

public:
  void* malloc(size_t size);
  void* calloc(size_t nmemb, size_t size);
  void* realloc(void*  ptr,   size_t size);
  void  free(void*  ptr);

public:
  static GMemHook& instance();
};

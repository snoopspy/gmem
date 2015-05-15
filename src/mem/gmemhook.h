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
  bool hook();
  bool unhook();

public:
  void* malloc(size_t size, const char* file, const int line);
  void* calloc(size_t nmemb, size_t size, const char* file, const int line);
  void* realloc(void* ptr, size_t size, const char* file, const int line);
  void free(void* ptr);

protected:
  bool active_ = false;
  void* (*malloc_)(size_t size) = nullptr;
  void* (*calloc_)(size_t nmemb, size_t size) = nullptr;
  void* (*realloc_)(void *ptr, size_t size) = nullptr;
  void (*free_)(void* ptr) = nullptr;

public:
  static GMemHook& instance();
};

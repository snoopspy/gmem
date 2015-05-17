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

#include <cstddef> // size_t

// ----------------------------------------------------------------------------
// GMemMgr
// ----------------------------------------------------------------------------
class GMemMgr {
public:
  static void start();
  static void stop();

public:
  static void* malloc (size_t size,               const char* file, const int line);
  static void  free   (void*  ptr,                const char* file, const int line);
  static void* calloc (size_t nmemb, size_t size, const char* file, const int line);
  static void* realloc(void*  ptr,   size_t size, const char* file, const int line);
};

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
// GMemLeak
// ----------------------------------------------------------------------------
class GMemLeak {
public:
  static void clear();
  static void check();
  static bool exists(void* ptr);
  static void add(void* ptr, size_t size, const char* file, const int line);
  static void del(void* ptr, const char* file, const int line);
};

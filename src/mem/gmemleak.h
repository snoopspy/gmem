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

#include <cstddef>

// ----------------------------------------------------------------------------
// GMemLeak
// ----------------------------------------------------------------------------
class GMemLeak {
protected:
  GMemLeak();
  virtual ~GMemLeak();

public:
  void clear();
  void check();
  bool exists(void* ptr);
  void add(void* ptr, size_t size, const char* file, const int line);
  void del(void* ptr);

public:
  static GMemLeak& instance();
};

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
protected:
  GMemMgr();
  virtual ~GMemMgr();

public:
  bool start();
  bool stop(bool leakCheck = true);
  bool restart();

public:
  void* malloc(size_t size, const char* file, const int line);
  void free(void* ptr);
  void* calloc(size_t nmemb, size_t size, const char* file, const int line);
  void* realloc(void* ptr, size_t size, const char* file, const int line);

public:
  static GMemMgr& instance();
};


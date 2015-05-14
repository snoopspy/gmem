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

#include <map>
#include <stddef.h> // size_t

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

  void* malloc(size_t size, const char* file, const int line);
  void* calloc(size_t nmemb, size_t size, const char* file, const int line);
  void* realloc(void *ptr, size_t size, const char* file, const int line);
  void free(void* ptr);

protected:
  bool active_ = false;
  void* (*oldMalloc_)(size_t size) = nullptr;
  void (*oldFree_)(void* ptr) = nullptr;
  struct Item {
    size_t size;
    char* file;
    int line;
  };
  typedef std::map<void*, Item> Items;
  Items items_;

public:
  static GMemMgr& instance();
};

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
  void start();
  void stop();
  void* add(void* ptr, size_t size, const char* file, const int line);
  void del(void* ptr);

protected:
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

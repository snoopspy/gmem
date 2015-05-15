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

#include <memory>
#include <iostream>
#include "gmemmgr.h"

template <typename T>
struct GMemAllocator : std::allocator<T>
{
  GMemAllocator() {}
  template <typename U> GMemAllocator(GMemAllocator<U> const&) {}

  typedef T value_type;
  template <typename U> struct rebind { typedef GMemAllocator<U> other; };
  T* allocate(size_t n) {
    T* res = (T*)GMemMgr::instance().malloc(n * sizeof(T), nullptr, 0);
    std::cout << "GMemAllocator::allocate   " << (void*)res << " " << n * sizeof(T) << std::endl;
    return res;
  }
  void deallocate(T* p, size_t n) {
    std::cout << "GMemAllocator::deallocate " << (void*)p << " " << n * sizeof(T) << std::endl;
    operator delete(p);
  }
};

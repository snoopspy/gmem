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

#include <stddef.h> // size_t

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// ----------------------------------------------------------------------------
// control functions
// ----------------------------------------------------------------------------
void gmem_start(void);
void gmem_stop(void);

// ----------------------------------------------------------------------------
// replace functions for c
// ----------------------------------------------------------------------------
void* gmem_malloc (              size_t size, const char* file, const int line);
void  gmem_free   (void *ptr,                 const char* file, const int line);
void* gmem_calloc (size_t nmemb, size_t size, const char* file, const int line);
void* gmem_realloc(void *ptr,    size_t size, const char* file, const int line);

#ifdef __cplusplus
}
#endif // __cplusplus

#ifdef __cplusplus

#include <new> // bad_alloc

// ----------------------------------------------------------------------------
// replace operators for cpp
// ----------------------------------------------------------------------------
void* operator new  (size_t size, const char* file, const int line) throw (std::bad_alloc);
void* operator new[](size_t size, const char* file, const int line) throw (std::bad_alloc);

#endif // __cplusplus

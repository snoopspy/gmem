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
#endif

// ----------------------------------------------------------------------------
// used internally
// ----------------------------------------------------------------------------
void* gmemmgr_add(void* ptr, size_t size, const char* file, const int line);
void  gmemmgr_del(void* ptr);

#ifdef __cplusplus
}
#endif

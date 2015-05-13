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
// export function
// ----------------------------------------------------------------------------
void gmem_mgr_start(void);
void gmem_mgr_stop(void);

// ----------------------------------------------------------------------------
// used internally
// ----------------------------------------------------------------------------
void* gmem_mgr_add(void* ptr, size_t size, const char* file, const int line);
void  gmem_mgr_del(void* ptr);

#ifdef __cplusplus
}
#endif

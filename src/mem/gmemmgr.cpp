#include <map>
#include <stdio.h>  // fprintf
#include "gmemmgr.h"

typedef struct {
  size_t size;
  char* file;
  int line;
} gmem_mgr_item_t;

typedef std::map<void*, gmem_mgr_item_t> gmem_mgr_t;

static gmem_mgr_t _gmem_mgr;

extern "C" void gmem_mgr_start(void) {
  _gmem_mgr.clear();
}

extern "C" void gmem_mgr_stop(void) {
  if (_gmem_mgr.size() <= 0) return;
  fprintf(stderr, "******************************************************************************\n");
  for (gmem_mgr_t::iterator it = _gmem_mgr.begin(); it != _gmem_mgr.end(); it++) {
    void* ptr = it->first;
    gmem_mgr_item_t& item = it->second;
    fprintf(stderr, "memory leak %p(%d bytes) %s:%d\n", ptr, (int)item.size, item.file, item.line);
  }
  fprintf(stderr, "******************************************************************************\n");
}

extern "C" void* gmem_mgr_add(void* ptr, size_t size, const char* file, const int line) {
  gmem_mgr_t::iterator it = _gmem_mgr.find(ptr);
  if (it != _gmem_mgr.end()) {
    fprintf(stderr, "ptr(%p) is already added size=%d file=%s line=%d\n", ptr, (int)size, file, line);
    return NULL;
  }
  gmem_mgr_item_t item;
  item.size = size;
  item.file = (char*)file;
  item.line = line;
  _gmem_mgr[ptr] = item;
  return ptr;
}

extern "C" void gmem_mgr_del(void* ptr) {
  if (ptr == NULL) {
    fprintf(stderr, "ptr is null\n");
    return;
  }
  gmem_mgr_t::iterator it = _gmem_mgr.find(ptr);
  if (it == _gmem_mgr.end()) return;
  _gmem_mgr.erase(it);
}

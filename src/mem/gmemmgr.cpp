#include <map>
#include <stdio.h>  // fprintf
#include "gmemmgr.h"

typedef struct {
  size_t size;
  char* file;
  int line;
} gmemmgr_item_t;

typedef std::map<void*, gmemmgr_item_t> gmemmgr_t;

static gmemmgr_t _gmemmgr;

void gmem_start(void) {
  _gmemmgr.clear();
}

void gmem_stop(void) {
  if (_gmemmgr.size() <= 0) return;
  fprintf(stderr, "******************************************************************************\n");
  for (gmemmgr_t::iterator it = _gmemmgr.begin(); it != _gmemmgr.end(); it++) {
    void* ptr = it->first;
    gmemmgr_item_t& item = it->second;
    fprintf(stderr, "memory leak %p(%d bytes) %s:%d\n", ptr, (int)item.size, item.file, item.line);
  }
  fprintf(stderr, "******************************************************************************\n");
}

void* gmemmgr_add(void* ptr, size_t size, const char* file, const int line) {
  gmemmgr_t::iterator it = _gmemmgr.find(ptr);
  if (it != _gmemmgr.end()) {
    fprintf(stderr, "ptr(%p) is already added size=%d file=%s line=%d\n", ptr, (int)size, file, line);
    return NULL;
  }
  gmemmgr_item_t item;
  item.size = size;
  item.file = (char*)file;
  item.line = line;
  _gmemmgr[ptr] = item;
  return ptr;
}

void gmemmgr_del(void* ptr) {
  if (ptr == NULL) {
    fprintf(stderr, "ptr is null\n");
    return;
  }
  gmemmgr_t::iterator it = _gmemmgr.find(ptr);
  if (it == _gmemmgr.end()) return;
  _gmemmgr.erase(it);
}

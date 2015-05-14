#include <stdio.h>  // fprintf
#include "gmemmgr.h"

// ----------------------------------------------------------------------------
// GMemMgr
// ----------------------------------------------------------------------------
GMemMgr::GMemMgr() {
  start();
}

GMemMgr::~GMemMgr() {
  stop();
}

void GMemMgr::start() {
  items_.clear();
}

void GMemMgr::stop() {
  if (items_.size() <= 0) return;
  fprintf(stderr, "******************************************************************************\n");
  for (Items::iterator it = items_.begin(); it != items_.end(); it++) {
    void* ptr = it->first;
    Item& item = it->second;
    fprintf(stderr, "memory leak %p(%d bytes) %s:%d\n", ptr, (int)item.size, item.file, item.line);
  }
  fprintf(stderr, "******************************************************************************\n");
  items_.clear();
}

void* GMemMgr::add(void* ptr, size_t size, const char* file, const int line) {
  Items::iterator it = items_.find(ptr);
  if (it != items_.end()) {
    fprintf(stderr, "ptr(%p) is already added size=%d file=%s line=%d\n", ptr, (int)size, file, line);
    return NULL;
  }
  Item item;
  item.size = size;
  item.file = (char*)file;
  item.line = line;
  items_[ptr] = item;
  return ptr;
}

void GMemMgr::del(void* ptr) {
  if (ptr == NULL) {
    fprintf(stderr, "ptr is null\n");
    return;
  }
  Items::iterator it = items_.find(ptr);
  if (it == items_.end()) return;
  items_.erase(it);
}

GMemMgr& GMemMgr::instance() {
  static GMemMgr instance;
  return instance;
}

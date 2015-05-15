#include <map>
#include "gmemallocator.h"
#include "gmemleak.h"

// ----------------------------------------------------------------------------
// GMemLeakImpl
// ----------------------------------------------------------------------------
class GMemLeakImpl : public GMemLeak {
public:
  struct Item {
    size_t size;
    char* file;
    int line;
  };
  typedef std::map<void*, Item, std::less<void*>, GMemAllocator<std::pair<const void*,Item>>> Items;
  Items items_;

public:
  void clear() {
    items_.clear();
  }

  void check() {
    if (items_.size() > 0) {
      fprintf(stderr, "******************************************************************************\n");
      for (Items::iterator it = items_.begin(); it != items_.end(); it++) {
        void* ptr = it->first;
        Item& item = it->second;
        fprintf(stderr, "memory leak %p(%d bytes) %s:%d\n", ptr, (int)item.size, item.file, item.line);
      }
      fprintf(stderr, "******************************************************************************\n");
    }
  }

  bool exists(void* ptr) {
    Items::iterator it = items_.find(ptr);
    return it != items_.end();
  }

  void add(void* ptr, size_t size, const char* file, const int line) {
    Item item;
    item.size = size;
    item.file = (char*)file;
    item.line = line;
    items_[ptr] = item;
  }

  void del(void* ptr) {
    Items::iterator it = items_.find(ptr);
    if (it == items_.end()) return;
    items_.erase(it);
  }
};

// ----------------------------------------------------------------------------
// GMemLeak
// ----------------------------------------------------------------------------
GMemLeak::GMemLeak() {
  clear();
}

GMemLeak::~GMemLeak() {
  check();
  clear();
}

void GMemLeak::clear() {
  ((GMemLeakImpl*)this)->clear();
}

void GMemLeak::check() {
  ((GMemLeakImpl*)this)->check();
}

bool GMemLeak::exists(void* ptr) {
  return ((GMemLeakImpl*)this)->exists(ptr);
}

void GMemLeak::add(void* ptr, size_t size, const char* file, const int line) {
  return ((GMemLeakImpl*)this)->add(ptr, size, file, line);
}

void GMemLeak::del(void* ptr) {
  return ((GMemLeakImpl*)this)->del(ptr);
}

GMemLeak& GMemLeak::instance() {
  static GMemLeakImpl _instance;
  return _instance;
}

#include <unordered_map>
#include "gmemallocator.h"
#include "gmemleak.h"

// ----------------------------------------------------------------------------
// GMemLeakImpl
// ----------------------------------------------------------------------------
class GMemLeakImpl {
public:
  struct Item {
    size_t size;
    char* file;
    int line;
  };
  typedef std::unordered_map<void*/*ptr*/, Item,
    std::hash<void*>,
    std::equal_to<void*>,
    GMemAllocator<std::pair<const void*,Item>>> Items;
  Items items_;

public:
  GMemLeakImpl() {
    clear();
  }

  virtual ~GMemLeakImpl() {
    check();
    clear();
  }

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
      items_.clear();
    }
  }

  bool exists(void* ptr) {
    Items::iterator it = items_.find(ptr);
    return it != items_.end();
  }

  void add(void* ptr, size_t size, const char* file, const int line) {
    // check duplicate // gilgil temp 2015.05.16
    Item item;
    item.size = size;
    item.file = (char*)file;
    item.line = line;
    items_[ptr] = item;
  }

  void del(void* ptr, const char* file, const int line) {
    Items::iterator it = items_.find(ptr);
    if (it == items_.end()) {
      fprintf(stderr, "******************************************************************************\n");
      fprintf(stderr, "can not find %p\n", ptr);
      fprintf(stderr, "******************************************************************************\n");
      return;
    }
    Item& item = it->second;
    if (file != item.file) {
      fprintf(stderr, "******************************************************************************\n");
      fprintf(stderr, "file is different %p %p %p\n", ptr, file, item.file);
      fprintf(stderr, "******************************************************************************\n");
    }
    if (line != item.line) {
      fprintf(stderr, "******************************************************************************\n");
      fprintf(stderr, "line is different %p %d %d\n", ptr, line, item.line);
      fprintf(stderr, "******************************************************************************\n");
    }
    items_.erase(it);
  }

  static GMemLeakImpl& instance() {
    static GMemLeakImpl _memLeakImpl;
    return _memLeakImpl;
  }
};

// ----------------------------------------------------------------------------
// GMemLeak
// ----------------------------------------------------------------------------
void GMemLeak::clear() {
  GMemLeakImpl::instance().clear();
}

void GMemLeak::check() {
  GMemLeakImpl::instance().check();
}

bool GMemLeak::exists(void* ptr) {
  return GMemLeakImpl::instance().exists(ptr);
}

void GMemLeak::add(void* ptr, size_t size, const char* file, const int line) {
  return GMemLeakImpl::instance().add(ptr, size, file, line);
}

void GMemLeak::del(void* ptr, const char* file, const int line) {
  return GMemLeakImpl::instance().del(ptr, file, line);
}

#include "gmemmgr.h"

int main() {
  GMemMgr::start();
  GMemMgr::_malloc(256, __FILE__, __LINE__);
  GMemMgr::stop();
}


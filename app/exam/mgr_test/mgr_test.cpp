#include <mem/gmemmgr.h>

int main() {
  GMemMgr::start();
  GMemMgr::malloc(256, __FILE__, __LINE__);
  GMemMgr::stop();
}


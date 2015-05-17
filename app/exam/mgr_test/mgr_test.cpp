#include <mem/gmemmgr.h>

int main() {
  GMemMgr::start();
  GMemMgr::malloc(1, __FILE__, __LINE__);
  GMemMgr::stop();
}


#include <stdlib.h>
#include <GMem>
#include <GMemMgr>

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-result"
#endif // __GNUC__

void malloc_test()
{
  gmem_mgr_start();
  malloc(256);
  gmem_mgr_stop();
}

void calloc_test()
{
  gmem_mgr_start();
  calloc(4, 256);
  gmem_mgr_stop();
}

void realloc_test()
{
  void *p;

  gmem_mgr_start();
  p = malloc(4);
  realloc(p, 4);
  gmem_mgr_stop();

  gmem_mgr_start();
  p = malloc(4);
  realloc(p, 400000);
  gmem_mgr_stop();
}

int main()
{
  malloc_test();
  calloc_test();
  realloc_test();
  return 0;
}

#include <stdlib.h>
#include <GMem>
#include <GMemMgr>

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-result"
#endif // __GNUC__

void malloc_test()
{
  gmemmgr_start();
  malloc(256);
  gmemmgr_stop();
}

void calloc_test()
{
  gmemmgr_start();
  calloc(4, 256);
  gmemmgr_stop();
}

void realloc_test()
{
  void *p;

  gmemmgr_start();
  p = malloc(4);
  realloc(p, 4);
  gmemmgr_stop();

  gmemmgr_start();
  p = malloc(4);
  realloc(p, 400000);
  gmemmgr_stop();
}

int main()
{
  malloc_test();
  calloc_test();
  realloc_test();
  return 0;
}

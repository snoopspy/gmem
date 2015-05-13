#include <stdlib.h>
#include <GMem>

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-result"
#endif // __GNUC__

void malloc_test()
{
  gmem_start();
  malloc(256);
  gmem_stop();
}

void calloc_test()
{
  gmem_start();
  calloc(4, 256);
  gmem_stop();
}

void realloc_test()
{
  void *p;

  gmem_start();
  p = malloc(4);
  realloc(p, 4);
  gmem_stop();

  gmem_start();
  p = malloc(4);
  realloc(p, 400000);
  gmem_stop();
}

int main()
{
  malloc_test();
  calloc_test();
  realloc_test();
  return 0;
}

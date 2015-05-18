#include <stdlib.h>
#include <GMem>

void malloc_test()
{
  void* p = malloc(256);
  free(p);
}

void calloc_test()
{
  void* p = calloc(2, 256);
  free(p);
}

void realloc_test()
{
  void* p = malloc(256);
  p = realloc(p, 256);
  free(p);

  p = malloc(256);
  p = realloc(p, 1024);
  free(p);
}

int main()
{
  malloc_test();
  calloc_test();
  realloc_test();
  return 0;
}

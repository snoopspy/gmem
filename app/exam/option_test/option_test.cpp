#include <stdlib.h>
#include <GMem>

int main()
{
  gmem_set_verbose(true);
  gmem_set_err(stdout);
  malloc(256);
  int* p = new int;
  delete p;
  return 0;
}

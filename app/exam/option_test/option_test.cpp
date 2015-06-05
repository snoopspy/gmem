#include <stdlib.h>
#include <GMem>

int main() {
  gmem_set_verbose(true);
  malloc(256); // memory leak
  int* p = new int;
  delete p;
  return 0;
}

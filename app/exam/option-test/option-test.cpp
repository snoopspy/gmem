#include <stdlib.h>
#include "gmem.h"

int main() {
  gmem_set_verbose(true);
  malloc(256); // memory leak
  int* p = new int;
  delete p;
}

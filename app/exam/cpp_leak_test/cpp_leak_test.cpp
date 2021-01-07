#include "gmem.h"

void new_test() {
  gmem_start();
  new int;
  gmem_stop();
}

void new_arr_test() {
  gmem_start();
  new int[256];
  gmem_stop();
}

int main() {
  new_test();
  new_arr_test();
  return 0;
}

#include <stdlib.h>
#include "gmem.h"

void first_test() {
  void *p = malloc(256);
  free(p);

  p = calloc(2, 256);
  free(p);

  p = malloc(256);
  p = realloc(p, 256);
  free(p);

  p = malloc(256);
  p = realloc(p, 1024);
  free(p);
}

#include "gmemcancel.h"
void cancel_test() {
  void *p = malloc(256);
  free(p);

  p = calloc(2, 256);
  free(p);

  p = malloc(256);
  p = realloc(p, 256);
  free(p);

  p = malloc(256);
  p = realloc(p, 1024);
  free(p);
}

#include "gmem.h"
void second_test() {
  void *p = malloc(256);
  free(p);

  p = calloc(2, 256);
  free(p);

  p = malloc(256);
  p = realloc(p, 256);
  free(p);

  p = malloc(256);
  p = realloc(p, 1024);
  free(p);
}

int main() {
  first_test();
  cancel_test();
  second_test();
}

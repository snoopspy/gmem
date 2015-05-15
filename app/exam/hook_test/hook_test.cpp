#include <cstdio>
#include <cstdlib>
#include <GMemHook>

void* myMalloc(size_t size) {
  (void)size;
  return (void*)1;
}

void* myCalloc(size_t nmemb, size_t size) {
  (void)nmemb;
  (void)size;
  return (void*)2;
}

void* myRealloc(void* ptr, size_t size) {
  (void)ptr;
  (void)size;
  return (void*)3;
}

void myFree(void *ptr) {
  (void)ptr;
}

int main() {
  GMemHook::instance().hook(myMalloc, myCalloc, myRealloc, myFree);
  void* p = malloc(256);
  if (p != (void*)1) {
    fprintf(stderr, "malloc return %p\n", p);
  }
  p = calloc(4, 256);
  if (p != (void*)2) {
    fprintf(stderr, "calloc return %p\n", p);
  }
  p = realloc(p, 400000);
  if (p != (void*)3) {
    fprintf(stderr, "realloc return %p\n", p);
  }
}

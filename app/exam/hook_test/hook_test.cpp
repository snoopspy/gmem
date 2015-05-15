#include <cstdio>
#include <cstdlib>
#include <GMemHook>

void* myMalloc(size_t size) {
  (void)size;
  return (void*)1;
}

void myFree(void *ptr) {
  (void)ptr;
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

int main() {
  GMemHook::instance().hook(myMalloc, myFree, myCalloc, myRealloc);

  void* p = malloc(256);
  printf("malloc  return %p\n", p);

  p = calloc(4, 256);
  printf("calloc  return %p\n", p);

  p = realloc(p, 400000);
  printf("realloc return %p\n", p);
}

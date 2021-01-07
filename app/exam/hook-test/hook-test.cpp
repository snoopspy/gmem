#include <cstdio>
#include <cstdlib>
#include "gmemhook.h"

void* _malloc(size_t size) {
  void* res = GMemHook::instance().orgMallocFunc_(size);
  printf("_malloc(%zu) return %p\n", size, res);
  return res;
}

void _free(void *ptr) {
  printf("_free(%p)\n", ptr);
  GMemHook::instance().orgFreeFunc_(ptr);
}

void* _calloc(size_t nmemb, size_t size) {
  void* res = GMemHook::instance().orgCallocFunc_(nmemb, size);
  printf("_calloc(%zu, %zu) return %p\n", nmemb, size, res);
  return res;
}

void* _realloc(void* ptr, size_t size) {
  void* res = GMemHook::instance().orgReallocFunc_(ptr, size);
  printf("_realloc(%p, %zu) return %p\n", ptr, size, res);
  return res;
}

void test() {
  printf("# malloc test\n");
  void* ptr = malloc(256);
  free(ptr);

  printf("# calloc test\n");
  ptr = calloc(2, 256);

  printf("# realloc test\n");
  ptr = realloc(ptr, 1024);
  free(ptr);
}

int main() {
  printf("first test\n");
  test();

  printf("\nhook test\n");
  GMemHook::instance().hook(_malloc, _free, _calloc, _realloc);
  test();

  printf("\nunhook test\n");
  GMemHook::instance().unhook();
  test();
}

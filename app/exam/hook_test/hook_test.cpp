#include <cstdio>
#include <cstdlib>
#include <GMemHook>

void* myMalloc(size_t size) {
  void* res = GMemHook::instance().orgMallocFunc_(size);
  printf("myMalloc(%zu) return %p\n", size, res);
  return res;
}

void myFree(void *ptr) {
  printf("myFree(%p)\n", ptr);
  GMemHook::instance().orgFreeFunc_(ptr);
}

void* myCalloc(size_t nmemb, size_t size) {
  void* res = GMemHook::instance().orgCallocFunc_(nmemb, size);
  printf("myCalloc(%zu, %zu) return %p\n", nmemb, size, res);
  return res;
}

void* myRealloc(void* ptr, size_t size) {
  void* res = GMemHook::instance().orgReallocFunc_(ptr, size);
  printf("myRealloc(%p, %zu) return %p\n", ptr, size, res);
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
  printf("hook test\n");
  GMemHook::instance().hook(myMalloc, myFree, myCalloc, myRealloc);
  test();

  printf("\nunhook test\n");
  GMemHook::instance().unhook();
  test();
}

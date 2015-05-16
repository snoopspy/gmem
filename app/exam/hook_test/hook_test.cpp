#include <cstdio>
#include <cstdlib>
#include <GMemHook>

void* malloc(size_t size) {
  void* res = GMemHook::instance().orgMallocFunc_(size);
  printf("malloc(%zu) return %p\n", size, res);
  return res;
}

void free(void *ptr) {
  printf("free(%p)\n", ptr);
  GMemHook::instance().orgFreeFunc_(ptr);
}

void* calloc(size_t nmemb, size_t size) {
  void* res = GMemHook::instance().orgCallocFunc_(nmemb, size);
  printf("calloc(%zu, %zu) return %p\n", nmemb, size, res);
  return res;
}

void* realloc(void* ptr, size_t size) {
  void* res = GMemHook::instance().orgReallocFunc_(ptr, size);
  printf("realloc(%p, %zu) return %p\n", ptr, size, res);
  return res;
}

int main() {
  printf("# malloc test\n");
  void* ptr = malloc(256);
  free(ptr);

  printf("\n# calloc test\n");
  ptr = calloc(4, 256);

  printf("\n# reaalloc test\n");
  ptr = realloc(ptr, 400000);
  free(ptr);
}

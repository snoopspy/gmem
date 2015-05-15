#include <GMemLeak>

int main() {
  GMemLeak& memLeak = GMemLeak::instance();
  memLeak.add((void*)1, 100, __FILE__, __LINE__);
  memLeak.add((void*)2, 200, __FILE__, __LINE__);
  memLeak.add((void*)3, 300, __FILE__, __LINE__);
  memLeak.del((void*)3);
  memLeak.check();
}

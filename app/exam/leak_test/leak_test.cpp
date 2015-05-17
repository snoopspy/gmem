#include <GMemLeak>

int main() {
  GMemLeak::add((void*)1, 100, __FILE__, __LINE__);
  GMemLeak::add((void*)1, 100, __FILE__, __LINE__);
  GMemLeak::add((void*)2, 200, __FILE__, __LINE__);
  GMemLeak::add((void*)3, 300, __FILE__, __LINE__);
  GMemLeak::del((void*)2, __FILE__, __LINE__);
  GMemLeak::check();
}

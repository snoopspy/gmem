#include <GMem>
#include <GMemMgr>

void new_test()
{
  gmemmgr_start();
  new int;
  gmemmgr_stop();
}

void new_arr_test()
{
  gmemmgr_start();
  new int[256];
  gmemmgr_stop();
}

int main()
{
  new_test();
  new_arr_test();
  return 0;
}

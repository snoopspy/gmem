#include <GMem>
#include <GMemMgr>

void new_test()
{
  gmem_mgr_start();
  new int;
  gmem_mgr_stop();
}

void new_arr_test()
{
  gmem_mgr_start();
  new int[256];
  gmem_mgr_stop();
}

int main()
{
  new_test();
  new_arr_test();
  return 0;
}

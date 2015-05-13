#include <GMem>

void first_test()
{
  delete new int;
  delete[] new int[256];
}

#include <GMemCancel>
void cancel_test()
{
  delete new int;
  delete[] new int[256];
}

#include <GMem>
void second_test()
{
  delete new int;
  delete[] new int[256];
}

int main()
{
  first_test();
  cancel_test();
  second_test();
  return 0;
}

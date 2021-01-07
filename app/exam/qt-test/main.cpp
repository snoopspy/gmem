#include <cstdio>
#include <QCoreApplication>

int main(int argc, char *argv[]) {
  printf("beg main\n");
  QCoreApplication a(argc, argv);
  printf("end main\n");
}

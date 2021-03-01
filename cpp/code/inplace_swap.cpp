#include <cstdio>

void inplace_swap(int *x, int *y) {
  *y = *x ^ *y;
  *x = *x ^ *y;
  *y = *x ^ *y;
}

int main(int argc, char *argv[]) {
  int *x = new int(5);
  int *y = new int(8);
  inplace_swap(x, y);
  printf("%d %d\n", *x, *y);
  return 0;
}

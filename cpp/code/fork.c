#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("Hello World (pid: %d)\n", (int)getpid());
  int rc1 = fork();
  int rc2 = fork();

  if (rc1 > 0 && rc2 > 0) {
    printf("Hello, I am parent of %d %d\n", rc1, rc2);
  } else if (rc1 == 0 && rc2 > 0) {
    printf("Hello, I am rc1, the parent of rc2\n");
  } else if (rc2 == 0 && rc1 > 0) {
    printf("Hello, I am rc2, the parent of rc1\n");
  }

  return 0;
}

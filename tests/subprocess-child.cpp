#include <stdio.h>

int main() {
  char buf[1024];
  scanf("%s", buf);

  printf("child stdout: %s\n", buf);
  fprintf(stderr, "child stderr\n");

  return 0;
}

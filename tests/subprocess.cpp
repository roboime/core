#include <stdio.h>

#include "interface/subprocess.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Usage: %s <subprocess name>\n", argv[0]);
    return 1;
  }

  ime::SubProcess child;
  child.start(argv[1]);

  char buffer[1024];
  child.write("Test\n");
  child.read(buffer, 1024);
  printf("%s", buffer);

  child.readErr(buffer, 1024);
  printf("%s", buffer);

  return 0;
}

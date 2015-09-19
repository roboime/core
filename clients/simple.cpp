#include <cstdio>

#include "core.h"

int main() {
  printf("RoboIME Core 2016\n");

  ime::Core core;

  core.start();

  return 0;
}

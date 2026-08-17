#include "core/init.h"
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::println(std::cerr, "Usage: cproj [command] <options>");
  }
  if (argc == 3) {
    cproj_core::handleInit(argv[3]);
  }
}

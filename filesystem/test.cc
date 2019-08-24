#include <iostream>

#include "FileSystem.h"

int main(int argc, char *argv[]) {

  if (argc != 2) 
    return -1;

  auto files = cpp::getFileNames(argv[1]);

  for (auto fname: files) {
    std::cout << fname << std::endl;
  }

  return 0;
}

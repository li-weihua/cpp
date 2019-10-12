#include <iostream>

#include "array.h"

int main() {

  Array a(10);

  for (int i=0; i<a.Length(); ++i) {
    a[i] = i;
  }

  for (int i=0; i<a.Length(); ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;

  auto b = std::move(a);

  std::cout << "b length: " << b.Length() << std::endl;
  std::cout << "a length: " << a.Length() << std::endl;

  return 0;
}

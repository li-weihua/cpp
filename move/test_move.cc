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

  Array b; 

  b = std::move(a);

  std::cout << "a length: " << a.Length() << std::endl;
  std::cout << "b length: " << b.Length() << std::endl;

  return 0;
}

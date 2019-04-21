#include <iostream>

#include "mathlib.h"

int main() {

  double x = 1.5;
  
  MathLib m;

  std::cout << "mysin(1.5) = " << mysin(1.5) << std::endl;
  std::cout << "MathLib::sin(1.5) = " << m.sin(1.5) << std::endl;

  return 0;
}

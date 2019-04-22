#include <iostream>

#include "mathlib.h"

int main() {

  double x = 1.5;
  
  mymath::MathLib m;

  std::cout << "mymath::mysin(1.5) = " << mymath::mysin(1.5) << std::endl;
  std::cout << "mymath::MathLib::sin(1.5) = " << m.sin(1.5) << std::endl;

  return 0;
}

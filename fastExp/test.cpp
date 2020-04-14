#include <iostream>
#include <stdio.h>
#include <immintrin.h>

using namespace std;


int main()
{
  union {float f; int i;} echo;

  echo.i = (127 + 127)<<23;

  printf("%.15e\n", echo.f);

  return 0;
}

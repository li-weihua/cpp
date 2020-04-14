#include <iostream>
#include <stdio.h>
#include <chrono>
#include <math.h>
#include "cephes_exp.h"
#include "fastSimdExp.h"

using namespace std;
using namespace std::chrono;

#define timecount(cmd)                                                    \
do {                                                                      \
  high_resolution_clock::time_point t1 = high_resolution_clock::now();    \
  cmd                                                                     \
  high_resolution_clock::time_point t2 = high_resolution_clock::now();    \
  auto duration = duration_cast<microseconds>( t2 - t1 ).count();         \
  std::cout << duration/1000 << " ms"<< std::endl;                        \
} while(0)


using FastExpFunc = float (*)(float );

FastExpFunc fastExp1 = &FastMath::fastExpf<7, AbsoluteError>;
FastExpFunc fastExp2 = &FastMath::fastExpf<7, RelativeError>;

int main()
{
  const float xmin = 1.f;
  const float xmax = 80.f;
  const float delta = 1.f;

  for (float x = xmin; x <= xmax; x += delta)
  {
    float r1 = cephes_expf(x);
    float r2 = FastMath::fastExpf<7, AbsoluteError>(x);
    printf("%.20e  %.20e\n" , r1 , r2);
  }
  
  /*
  // benchmark loop
  const float b1_delta = 0.000004f;

  float b1_sum1 = 0, b1_sum2 = 0;

  timecount(
    for (float x = xmin; x <= xmax; x += b1_delta) 
    {
      b1_sum1 += cephes_expf(x);
    }
  );

  timecount(
    for (float x = xmin; x <= xmax; x += b1_delta) 
    {
      b1_sum2 += FastMath::fastExp_7r_1f(x);
    }
  );

  printf("\n%.15e %.15e\n\n", b1_sum1, b1_sum2);
  */

  return 0;
}

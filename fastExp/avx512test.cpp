#include <iostream>
#include <stdio.h>
#include <immintrin.h>
#include <chrono>
#include "fastExpr_scale.hpp"
#include "orgFastSimdExp.h"
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

// bounding function pointer
using FastExpFunc = float (*)(float x);
using SimdExpFunc = __m512 (*)(__m512 &x);

FastExpFunc fastExp = &FastMath::fastExp_4r_1f;

SimdExpFunc simdExp = &FastMath::fastExp16f_AVX512<4, RelativeError>;

int main()
{
  //check accuracy
  const int block = 16;
  __attribute__((aligned(64))) float a[block];
  __attribute__((aligned(64))) float b[block];
  __m512 mx, my;

  for (float i=-90; i<=90; i += 1.f)
  {
    a[0] = i;
    float r1 = fastExp(i);
    mx = _mm512_load_ps(a);
    mx = simdExp(mx);
    _mm512_store_ps(a, mx);
    float r2 = a[0];
   printf("%.20e %.20e\n", r1, r2);
  }

  return 0;
}



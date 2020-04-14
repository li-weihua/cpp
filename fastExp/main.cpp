#include <iostream>
#include <stdio.h>
#include <immintrin.h>
#include <chrono>
#include "fastExpr_scalar.hpp"
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
using SimdExpFunc = __m256 (*)(__m256 &x);

FastExpFunc fastExp1 = &FastMath::fastExp_4r_1f;
FastExpFunc fastExp = fastExp1;
FastExpFunc fastExp2 = &FastMath::fastExpf<4, RelativeError>;

SimdExpFunc simdExp1 = &FastMath::fastExp8f_AVX_4r;
SimdExpFunc simdExp2 = &FastMath::fastExp8f_AVX<4, RelativeError>;
//SimdExpFunc simdExp3 = &FastMath::fastExp8f_AVX2_FMA<4, RelativeError>;

int main()
{
  // benchmark loop
  const float xmin = -90.f;
  const float xmax = 50.f;
  const float b1_delta = 0.000004f;

  float b1_sum1 = 0, b1_sum2 = 0;

  timecount(
    for (float x = xmin; x <= xmax; x += b1_delta) 
    {
      b1_sum1 += fastExp1(x);
    }
  );

  timecount(
    for (float x = xmin; x <= xmax; x += b1_delta) 
    {
      b1_sum2 += fastExp2(x);
    }
  );

  b1_sum1 = b1_sum2 = 0;

  timecount(
    for (float x = xmin; x <= xmax; x += b1_delta) 
    {
      b1_sum1 += fastExp1(x);
    }
  );

  timecount(
    for (float x = xmin; x <= xmax; x += b1_delta) 
    {
      b1_sum2 += fastExp2(x);
    }
  );


  printf("\n%.15e %.15e\n\n", b1_sum1, b1_sum2);


  /*
  //check accuracy
  __attribute__((aligned(64))) float a[8];
  __attribute__((aligned(64))) float b[8];
  __m256 mx, my;
  for (float i=-90; i<=80; i += 1.f)
  {
    a[0] = i; b[0] = i;
    mx = _mm256_load_ps(a);
    my = _mm256_load_ps(b);

    mx = simdExp1(mx);
    my = simdExp2(my);

    _mm256_store_ps(a, mx);
    _mm256_store_ps(b, my);

    float r1 = a[0];
    float r2 = b[0];

   printf("%.20e %.20e\n", r1, r2);
  }
  */

  // parameters
  const int block = 8;
  const float fmin = -80.0f;
  const float fmax = 50.0f;
  const float delta = 0.0000005f;
  const float deltablock = delta * block;

  float sum1 = 0, sum2 = 0, sum3;

  float x1 = fmin + 0 * delta; float x2 = fmin + 1 * delta;
  float x3 = fmin + 2 * delta; float x4 = fmin + 3 * delta;
  float x5 = fmin + 4 * delta; float x6 = fmin + 5 * delta;
  float x7 = fmin + 6 * delta; float x8 = fmin + 7 * delta;

  timecount(
      while (x8 <= fmax)
      {
        sum1 += fastExp(x1); sum1 += fastExp(x2);
        sum1 += fastExp(x3); sum1 += fastExp(x4);
        sum1 += fastExp(x5); sum1 += fastExp(x6);
        sum1 += fastExp(x7); sum1 += fastExp(x8);
        x1 += deltablock; x2 += deltablock; 
        x3 += deltablock; x4 += deltablock;
        x5 += deltablock; x6 += deltablock; 
        x7 += deltablock; x8 += deltablock;
      }
  );


  x1 = fmin + 0 * delta; x2 = fmin + 1 * delta;
  x3 = fmin + 2 * delta; x4 = fmin + 3 * delta;
  x5 = fmin + 4 * delta; x6 = fmin + 5 * delta;
  x7 = fmin + 6 * delta; x8 = fmin + 7 * delta;

  __m256 mx, mr = _mm256_set1_ps(0.f);

  float arr[block] __attribute__((aligned(64)));
  timecount(
    while (x8 <= fmax)
    {
      mx = _mm256_set_ps(x8, x7, x6, x5, x4, x3, x2, x1);
      mr = _mm256_add_ps(mr, simdExp1(mx));
      x1 += deltablock; x2 += deltablock; 
      x3 += deltablock; x4 += deltablock;
      x5 += deltablock; x6 += deltablock; 
      x7 += deltablock; x8 += deltablock;
    }
  );

  _mm256_store_ps(arr, mr);

  for (int i=0; i<block; i++)
  {
    sum2 += arr[i];
  }

  x1 = fmin + 0 * delta; x2 = fmin + 1 * delta;
  x3 = fmin + 2 * delta; x4 = fmin + 3 * delta;
  x5 = fmin + 4 * delta; x6 = fmin + 5 * delta;
  x7 = fmin + 6 * delta; x8 = fmin + 7 * delta;

  mr = _mm256_set1_ps(0.f);

  timecount(
    while (x8 <= fmax)
    {
      mx = _mm256_set_ps(x8, x7, x6, x5, x4, x3, x2, x1);
      mr = _mm256_add_ps(mr, simdExp2(mx));
      x1 += deltablock; x2 += deltablock; 
      x3 += deltablock; x4 += deltablock;
      x5 += deltablock; x6 += deltablock; 
      x7 += deltablock; x8 += deltablock;
    }
  );

  _mm256_store_ps(arr, mr);

  for (int i=0; i<block; i++)
  {
    sum3 += arr[i];
  }


  printf("\n");
  printf("%.20e\n", sum1);
  printf("%.20e\n", sum2);
  printf("%.20e\n", sum3);

  return 0;
}



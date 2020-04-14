#include <iostream>
#include <chrono>
#include <stdio.h>
#include <math.h>
#include <immintrin.h>

using namespace std;
using namespace std::chrono;

#define timecount(cmd)                                                    \
do {                                                                      \
  high_resolution_clock::time_point t1 = high_resolution_clock::now();    \
  cmd                                                                     \
  high_resolution_clock::time_point t2 = high_resolution_clock::now();    \
  auto duration = duration_cast<microseconds>( t2 - t1 ).count();         \
  std::cout << duration/1000 << " ms"<< std::endl;                        \
}while(0)

static inline float myExp(float x)
{
  const float xmin = -87.3;
  const float xmax = 88;
  if ( x < xmin)
  {
    return 0.0;
  }
  else if (x > xmax)
  {
    return 1e127;
  }

  union
  { 
    float f;
    int i;
  } echo;
  const int shift = (1<<23);
  const int bias = 127;
  const float log2e = 1.4426950408889634;
  const float ln2 = 0.693147180559945;
  const float p3_0 = 0.000187982244110;
  const float p3_1 = 0.303161683081084;
  const float p3_2 = -0.224126658503536;
  const float p3_3 = -0.079019992248559;
  float xp = x*log2e;
  float xf = xp - floor(xp);
  x = p3_3;
  x = x*xf + p3_2;
  x = x*xf + p3_1;
  x = x*xf + p3_0;
  xp -= x;
  echo.i = shift*(xp + bias);
  return echo.f;
}

static inline __m256 exp256_ps_avx2_fma(__m256 &x)
{
  const __m256 shift = _mm256_set1_ps(8388608); // 1<<23 or 2^23
  const __m256 bias = _mm256_set1_ps(1065353216); //127*2^23
  const __m256 log2e = _mm256_set1_ps(1.442695040888963);
  const __m256 p0 = _mm256_set1_ps(0.000187982244110);
  const __m256 p1 = _mm256_set1_ps(0.303161683081084);
  const __m256 p2 = _mm256_set1_ps(-0.224126658503536);
  const __m256 p3 = _mm256_set1_ps(-0.079019992248559);
  const __m256 xmin = _mm256_set1_ps(-87.3); // 126/log2e
  __m256 mask = _mm256_cmp_ps(x, xmin, _CMP_GT_OS); // great than //3
  __m256 xp = _mm256_mul_ps(x, log2e);  //5
  __m256 xf = _mm256_sub_ps(xp, _mm256_floor_ps(xp));

  __m256 xs = p3;
  xs = _mm256_add_ps(_mm256_mul_ps(xs, xf), p2); //FMA optimize // 8
  xs = _mm256_add_ps(_mm256_mul_ps(xs, xf), p1); //FMA //8
  xs = _mm256_add_ps(_mm256_mul_ps(xs, xf), p0); //FMA //8
  xp = _mm256_sub_ps(xp, xs);
  xp = _mm256_add_ps(_mm256_mul_ps(xp, shift), bias); //FMA //8

  __m256i xi = _mm256_cvtps_epi32(xp); //3
  return _mm256_and_ps(_mm256_castsi256_ps(xi), mask); //6
}


int main()
{
  /*
  const int block = 8;
  float a[block] __attribute__((aligned(64))) = {-1,-2,-3,-4,-5,-6,-7, -200};
  float b[block] __attribute__((aligned(64)));

  for(int i=0; i > -100; i--)
  {
    a[0] = i;
    __m256 x = _mm256_load_ps(a);
    x = exp256_ps_avx2_fma(x);
    _mm256_store_ps(b, x);

    float r0 = expf(a[0]);
    printf("%f %.10e %.10e %.2f/10000\n", a[0], b[0], r0, fabs(b[0] - r0)/r0*10000);
  }
  */

  // benchmarking
  const int nLoop = 512*512*51*51;
  const int block = 8;

  float x = 26;
  __m256 v8fx = _mm256_set1_ps(x);

  float sum1 = 0;
  float sum2 = 0;

  timecount(
  for (int i=0; i < nLoop; i++)
  {
      sum1 += expf(x);
  }
  );

  timecount(
  for (int i=0; i < nLoop; i++)
  {
     sum2 += myExp(x);
  }
  );

  __m256 r = _mm256_set1_ps(0);
  float b[block] __attribute__((aligned(64)));

  timecount(
  for (int i=0; i < nLoop/block; i++)
  {
    r = _mm256_add_ps(r, exp256_ps_avx2_fma(v8fx));
  }
  );

  _mm256_store_ps(b,r);

  printf("\n-----------\n");
  printf("%f\n",sum1);
  printf("%f\n",sum2);
  printf("%f\n", b[0]);

  return 0;
}

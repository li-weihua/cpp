//
// version 1: e^y =  2^(xi+xf) = 2^xi* 2^xf = 2^xi * Pn(xf)
// Pn(x) = p4*x^4 + p3*x^3 + p2*x^2 + p1*x + p0

inline float fastExp1s_4r(float x)
{
  union {float f; const int i = 0x7f800000;} PositiveInf;
  //0x7f800000 positive infinity
  const float xmin = -88.029697f;
  const float xmax = 88.722835f;
  const float log2e = 1.44269504088896f;
  const float p[5] = {
    1.00000259337069f,
    0.693003834470096f,
    0.241442756891235f,
    5.20114606105450e-2,
    1.35341679160618e-2
  };

  if ( x < xmin)
  {
    return 0.0;
  }
  else if (x > xmax)
  {
    return PositiveInf.f;
  }

  union {float f; int i;} echo;
  const int shift = 23;
  const int bias = 127;

  x = x*log2e; 
  int xi = int(floor(x));
  echo.i = (xi + bias) << shift;
  float xf = x - xi;
  x = p[4];
  x = x*xf + p[3];
  x = x*xf + p[2];
  x = x*xf + p[1];
  x = x*xf + p[0];
  return x*echo.f;
}

// 4th dgree of polynomial 
inline __m256 fastExp8f_AVX_4r(__m256 &x)
{
  const __m256 shift = _mm256_set1_ps(1<<23);
  const __m256 bias = _mm256_set1_ps(127.0f);
  const __m256 log2e = _mm256_set1_ps(1.442695040888963f);
  const __m256 xmin = _mm256_set1_ps(-127.0f);

  __m256 xp = _mm256_mul_ps(x, log2e);
  __m256 xi = _mm256_floor_ps(xp);
  __m256 xf = _mm256_sub_ps(xp, xi);

  __m256 mask = _mm256_cmp_ps(xi, xmin, _CMP_GE_OS); // great than or equal

  xi = _mm256_add_ps(xi, bias);
  xi = _mm256_mul_ps(xi, shift);

  const __m256 p0 =  _mm256_set1_ps(1.00000259337069f);
  const __m256 p1 =  _mm256_set1_ps(0.693003834470096f);
  const __m256 p2 =  _mm256_set1_ps(0.241442756891235f);
  const __m256 p3 =  _mm256_set1_ps(5.20114606105450e-2);
  const __m256 p4 =  _mm256_set1_ps(1.35341679160618e-2);

  xp = p4;
  xp = _mm256_add_ps(_mm256_mul_ps(xp, xf), p3);
  xp = _mm256_add_ps(_mm256_mul_ps(xp, xf), p2);
  xp = _mm256_add_ps(_mm256_mul_ps(xp, xf), p1);
  xp = _mm256_add_ps(_mm256_mul_ps(xp, xf), p0);

  __m256i rxi = _mm256_cvtps_epi32(xi);
  xf = _mm256_castsi256_ps(rxi);
  return _mm256_and_ps(_mm256_mul_ps(xf, xp), mask);
}


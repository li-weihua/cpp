
namespace FastMath {

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

} // namespace FastMath

#ifndef FASTMATH_SIMDEXP_M1_H
#define FASTMATH_SIMDEXP_M1_H

#include <math.h>
#include <immintrin.h>
// fitting method: minimize abs error or relative error
enum OptionError {AbsoluteError, RelativeError};

namespace FastMath {

////
template<int n, OptionError errtype>
struct Coefficient {}; // limit n = 3,4,5,6,7

template<>
struct Coefficient<3, AbsoluteError>
{
  const float aerr = 1.07034e-4;
  const float rerr = 1.07034e-4;
  const float p[4] = {
    0.999892965650529f,
    0.696457394993351f,
    0.224338364786827f,
    7.92042402198215e-2 
  };
};

template<>
struct Coefficient<3, RelativeError>
{
  const float aerr = 1.49562e-4;
  const float rerr = 7.47814e-5;
  const float p[4] = {
    0.999925218562710f,
    0.695833540494824f,
    0.226067155427249f,
    7.80245226406373e-2,
  };
};

template<>
struct Coefficient<4, AbsoluteError>
{
  const float aerr = 3.70447e-6;
  const float rerr = 3.70447e-6;
  const float p[5] = {
    1.00000370446593f,
    0.692966122661638f,
    0.241638445723760f,
    5.16903582079031e-2,
    1.36976644748399e-2 
  };
};

template<>
struct Coefficient<4, RelativeError>
{
  const float aerr = 5.18674e-6;
  const float rerr = 2.59337e-6;
  const float p[5] = {
    1.00000259337069f,
    0.693003834470096f,
    0.241442756891235f,
    5.20114606105450e-2,
    1.35341679160618e-2
  };
};

template<>
struct Coefficient<5, AbsoluteError>
{
  const float aerr = 1.06889e-7;
  const float rerr = 1.06889e-7; 
  const float p[6] = {
    0.999999893110827f,
    0.693154752475167f,
    0.240139711090769f,
    5.58662463045207e-2,
    8.94282898410913e-3,
    1.89646114543331e-3
  };
};

template<>
struct Coefficient<5, RelativeError>
{
  const float aerr = 1.49873e-7;
  const float rerr = 7.49365e-8;
  const float p[6] = {
    0.999999925063526f,
    0.693153073200169f,
    0.240153617044375f,
    5.58263180532957e-2,
    8.98934009049467e-3,
    1.87757667519148e-3
  };
};

template<>
struct Coefficient<6, AbsoluteError>
{
  const float aerr = 2.64427e-9;
  const float rerr = 2.64427e-9;
  const float p[7] = {
    1.00000000264427f,
    0.693146924564394f,
    0.240230550187546f,
    5.54802209975679e-2,
    9.68497632196016e-3,
    1.23843034972398e-3,
    2.18892290263222e-4
  };
};

template<>
struct Coefficient<6, RelativeError>
{
  const float aerr = 3.71160e-9;
  const float rerr = 1.85580e-9;
  const float p[7] = {
    1.00000000185580f,
    0.693146983840619f,
    0.240229836273961f,
    5.54833419845672e-2,
    9.67884099612836e-3,
    1.24396878272184e-3,
    2.17022554601337e-4
  };
};

template<>
struct Coefficient<7, AbsoluteError>
{
  const float aerr = 5.72477e-11;
  const float rerr = 5.72477e-11;
  const float p[8] = {
    0.999999999942752f,
    0.693147187818368f,
    0.240226356040224f,
    5.55053023513571e-2,
    9.61350610055018e-3,
    1.34302452205913e-3,
    1.42962417079442e-4,
    2.16607503620492e-5
  };
};

template<>
struct Coefficient<7, RelativeError>
{
  const float aerr = 8.04220e-11; 
  const float rerr = 4.02110e-11;
  const float p[8] = {
    0.999999999959789f,
    0.693147186083888f,
    0.240226384618011f,
    5.55051268595021e-2,
    9.61401701198981e-3,
    1.34226348230188e-3,
    1.43523140402616e-4,
    2.14987636931779e-5
  };
};

// scalar vesion loop expansion
template<int n>
inline float HornerEval(float &x, float &xf, const float p[])
{
  x = x*xf + p[n];
  return HornerEval<n-1>(x, xf, p);
}

template<>
inline float HornerEval<0>(float &x, float &xf, const float p[])
{
  return x*xf + p[0];
}

// scalar version
template <int n, OptionError errtype>
inline float fastExpf(float x)
{
  //0x7f800000 positive infinity
  union {float f; const int i = 0x7f800000;} PositiveInf;
  const float xmin = -88.029697f;
  const float xmax = 88.722835f;
  const float log2e = 1.44269504088896f;

  if ( x < xmin)
  {
    return 0.0;
  }
  else if (x > xmax)
  {
    return PositiveInf.f;
  }

  x = x*log2e; 
  union {float f; int i;} echo;
  const int shift = 23;
  const int bias = 127;

  int xi = int(floor(x));
  echo.i = (xi + bias) << shift;
  float xf = x - xi;

  const Coefficient<n, errtype> coeff;
  x = coeff.p[n];

  // loop expansion using template evaluation
  x = HornerEval<n-1>(x, xf, coeff.p);
  return x*echo.f;
}

// AVX vesion loop expansion
template<int n>
inline __m256 HornerEval_AVX(__m256 &x, __m256 &xf, const float p[])
{
  x = _mm256_add_ps(_mm256_mul_ps(x, xf), _mm256_set1_ps(p[n]));
  return HornerEval_AVX<n-1>(x, xf, p);
}

template<>
inline __m256 HornerEval_AVX<0>(__m256 &x, __m256 &xf, const float p[])
{
  return _mm256_add_ps(_mm256_mul_ps(x, xf), _mm256_set1_ps(p[0]));
}

// AVX version fast exp
template<int n, OptionError opttype>
inline __m256 fastExp8f_AVX(__m256 &x)
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

  const Coefficient<n, opttype> coeff;

  xp = _mm256_set1_ps(coeff.p[n]);
  xp = HornerEval_AVX<n-1>(xp, xf, coeff.p);

  __m256i rxi = _mm256_cvtps_epi32(xi);
  xf = _mm256_castsi256_ps(rxi);
  return _mm256_and_ps(_mm256_mul_ps(xf, xp), mask);
}

// FMA vesion loop expansion
template<int n>
inline __m256 HornerEval_FMA(__m256 &x, __m256 &xf, const float p[])
{
  x = _mm256_fmadd_ps(x, xf, _mm256_set1_ps(p[n]));
  return HornerEval_AVX<n-1>(x, xf, p);
}

template<>
inline __m256 HornerEval_FMA<0>(__m256 &x, __m256 &xf, const float p[])
{
  return _mm256_fmadd_ps(x, xf, _mm256_set1_ps(p[0]));
}

#if 0
// AVX2-FMA version fast exp
template<int n, OptionError opttype>
inline __m256 fastExp8f_AVX2_FMA(__m256 &x)
{
  const __m256 shift = _mm256_set1_ps(1<<23);
  const __m256 bias = _mm256_set1_ps(127.0f * (1<<23));
  const __m256 log2e = _mm256_set1_ps(1.442695040888963f);
  const __m256 xmin = _mm256_set1_ps(-127.0f);

  __m256 xp = _mm256_mul_ps(x, log2e);
  __m256 xi = _mm256_floor_ps(xp);
  __m256 xf = _mm256_sub_ps(xp, xi);

  __m256 mask = _mm256_cmp_ps(xi, xmin, _CMP_GE_OS); // great than or equal

//  xi = _mm256_add_ps(xi, bias);
 // xi = _mm256_mul_ps(xi, shift);
  xi = _mm256_fmadd_ps(xi, bias, shift);

  const Coefficient<n, opttype> coeff;

  xp = _mm256_set1_ps(coeff.p[n]);
  xp = HornerEval_FMA<n-1>(xp, xf, coeff.p);

  __m256i rxi = _mm256_cvtps_epi32(xi);
  xf = _mm256_castsi256_ps(rxi);
  return _mm256_and_ps(_mm256_mul_ps(xf, xp), mask);
}

// AVX-512 vesion loop expansion
template<int n>
inline __m512 HornerEval_AVX512(__m512 &x, __m512 &xf, const float p[])
{
  x = _mm512_fmadd_ps(x, xf, _mm512_set1_ps(p[n]));
  return HornerEval_AVX512<n-1>(x, xf, p);
}

template<>
inline __m512 HornerEval_AVX512<0>(__m512 &x, __m512 &xf, const float p[])
{
  return _mm512_fmadd_ps(x, xf, _mm512_set1_ps(p[0]));
}

// AVX512 version fast exp
template<int n, OptionError opttype>
inline __m512 fastExp16f_AVX512(__m512 &x)
{
  const __m512 shift = _mm512_set1_ps(1<<23);
  const __m512 bias = _mm512_set1_ps(127.0f *(1<<23));
  const __m512 log2e = _mm512_set1_ps(1.442695040888963f);
  const __m512 xmin = _mm512_set1_ps(-127.0f);
  const __m512 xmax = _mm512_set1_ps(126.0f);

  __m512 xp = _mm512_mul_ps(x, log2e);
  __m512 xi = _mm512_floor_ps(xp);
  __m512 xf = _mm512_sub_ps(xp, xi);

  __mmask16 mask1 = _mm512_cmp_ps_mask(xi, xmin, _CMP_GE_OS); // great than or equal
  __mmask16 mask2 = _mm512_cmp_ps_mask(xi, xmax, _CMP_LE_OS); // less than or equal

  xi = _mm512_fmadd_ps(xi, shift, bias);

  const Coefficient<n, opttype> coeff;

  xp = _mm512_set1_ps(coeff.p[n]);
  xp = HornerEval_AVX512<n-1>(xp, xf, coeff.p);

  __m512i rxi = _mm512_cvtps_epi32(xi);
  xf = _mm512_castsi512_ps(rxi);
  const __m512 src1 = _mm512_set1_ps(0.f);
  const __m512 src2 = _mm512_castsi512_ps(_mm512_set1_epi32(0x7f800000));
  xp = _mm512_mask_mul_ps(src1, mask1, xp, xf);
  return _mm512_mask_blend_ps(mask2, src2, xp);
}

#endif

// explicit instantiation
template float fastExpf<3, RelativeError>(float);
template float fastExpf<4, RelativeError>(float);
template float fastExpf<5, RelativeError>(float);
template float fastExpf<6, RelativeError>(float);
template float fastExpf<7, RelativeError>(float);

} // namespace FastMath

#endif // FASTMATH_SIMDEXP_M1_H

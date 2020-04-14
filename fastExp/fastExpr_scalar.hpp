#include <math.h>
//
// version 1: e^y =  2^(xi+xf) = 2^xi* 2^xf = 2^xi * Pn(xf)
// Pn(x) = p4*x^4 + p3*x^3 + p2*x^2 + p1*x + p0
// 

namespace FastMath {

inline float fastExp_3r_1f(float x) 
{
  union {float f; const int i = 0x7f800000;} PositiveInf;
  //0x7f800000 positive infinity
  const float xmin = -88.029697f;
  const float xmax = 88.722835f;
  const float log2e = 1.44269504088896f;
  const float p[4] = {
    0.999925218562710f,
    0.695833540494824f,
    0.226067155427249f,
    7.80245226406373e-2,
  };

  if ( x < xmin)
  {
    return 0.f;
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
  x = p[3];
  x = x*xf + p[2];
  x = x*xf + p[1];
  x = x*xf + p[0];
  return x*echo.f;
}

//
inline float fastExp_4r_1f(float x)
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

//
inline float fastExp_5r_1f(float x)
{
  union {float f; const int i = 0x7f800000;} PositiveInf;
  //0x7f800000 positive infinity
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

  union {float f; int i;} echo;
  const int shift = 23;
  const int bias = 127;
  const float p[6] = {
    0.999999925063526f,
    0.693153073200169f,
    0.240153617044375f,
    5.58263180532957e-2,
    8.98934009049467e-3,
    1.87757667519148e-3
  };

  x = x*log2e; 
  int xi = int(floor(x));
  echo.i = (xi + bias) << shift;
  float xf = x - xi;
  x = p[5];
  x = x*xf + p[4];
  x = x*xf + p[3];
  x = x*xf + p[2];
  x = x*xf + p[1];
  x = x*xf + p[0];
  return x*echo.f;
}

//
inline float fastExp_6r_1f(float x)
{
  union {float f; const int i = 0x7f800000;} PositiveInf;
  //0x7f800000 positive infinity
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

  union {float f; int i;} echo;
  const int shift = 23;
  const int bias = 127;
  const float p[7] = {
    1.00000000185580f,
    0.693146983840619f,
    0.240229836273961f,
    5.54833419845672e-2,
    9.67884099612836e-3,
    1.24396878272184e-3,
    2.17022554601337e-4
  };

  x = x*log2e; 
  int xi = int(floor(x));
  echo.i = (xi + bias) << shift;
  float xf = x - xi;
  x = p[6];
  x = x*xf + p[5];
  x = x*xf + p[4];
  x = x*xf + p[3];
  x = x*xf + p[2];
  x = x*xf + p[1];
  x = x*xf + p[0];
  return x*echo.f;
}

//
inline float fastExp_7r_1f(float x)
{
  union {float f; const int i = 0x7f800000;} PositiveInf;
  //0x7f800000 positive infinity
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

  union {float f; int i;} echo;
  const int shift = 23;
  const int bias = 127;
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

  x = x*log2e; 
  int xi = int(floor(x));
  echo.i = (xi + bias) << shift;
  float xf = x - xi;
  x = p[7];
  x = x*xf + p[6];
  x = x*xf + p[5];
  x = x*xf + p[4];
  x = x*xf + p[3];
  x = x*xf + p[2];
  x = x*xf + p[1];
  x = x*xf + p[0];
  return x*echo.f;
}

} // namespace FastMath

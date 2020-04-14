
#include <math.h>

float cephes_expf(float x)
{
  const float exp_hi = 88.3762626647950f;
  const float exp_lo = -88.3762626647949f;

  const float C1 =   0.693359375;
  const float C2 =  -2.12194440e-4;
  const float log2e = 1.44269504088896341f;
  const int shift = 23;
  const int bias = 127;
  union {float f; int i;} echo;

  float z = floor(x*log2e + 0.5); /* floor() truncates toward -infinity. */
  x -= z * C1;
  x -= z * C2;
  int n = z;
  echo.i = (n+bias) << shift;

  z = x * x;
  /* Theoretical peak relative error in [-0.5, +0.5] is 4.2e-9. */
  z =
  ((((( 1.9875691500E-4  * x
     + 1.3981999507E-3) * x
     + 8.3334519073E-3) * x
     + 4.1665795894E-2) * x
     + 1.6666665459E-1) * x
     + 5.0000001201E-1) * z
     + x
     + 1.0;

  return  echo.f * z;
}


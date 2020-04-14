#include <stdio.h>
#include <math.h>
#include <mpfr.h>

float fastAtan(float x)
{
  float x2 = x * x;
  //const float p0 = -0.333332863973f;
  //const float p1 = 0.199268615938f;
  const float p0 = -0.33333170414f;
  const float p1 = 0.19897942245f;
  return  x + x*x2*(p0 + p1*x2);
}

float cephesAtan(float x)
{
  float z = x * x;
 return ((( 8.05374449538e-2 * z
          - 1.38776856032E-1) * z
          + 1.99777106478E-1) * z 
          - 3.33329491539E-1) * z * x
          + x;
}

int main()
{
  const double pi = 3.141592653589793238;
  const double fb = tan(4.1*pi/180);
  const double delta = 1e-6;

  double  maxdiff = 0;

  for (double x=-fb; x <= fb; x += delta)
  {
    double diff = fastAtan(x)/atan(x) -1;
    //double diff = atanf(x) - atan(x);
    //double diff = cephesAtan(x) - atan(x);
    if (diff > maxdiff)
    {
      maxdiff = diff;
    }
  }

  printf("%.10e\n", maxdiff);

  return 0;
}


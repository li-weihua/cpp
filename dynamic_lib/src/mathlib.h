#pragma once

#ifdef _WIN32 
#if defined(MATHLIB_BUILD_SHARED_LIBS)
#define MATH_API  __declspec(dllexport)
#else
#define MATH_API  __declspec(dllimport)
#endif
#else // _WIN32
#if defined(__GNUC__)
#define MATH_API __attribute__((__visibility__("default")))
#else // __GNUC__
#define MATH_API
#endif // __GNUC__
#endif

namespace mymath {

MATH_API double mysin(double x);

class MATH_API MathLib {
  public:
    double sin(double x);
};

class MathBase {
public:
  virtual double sin(double x) = 0;
};

} // namespace mymath

// create and delete object api
extern "C" MATH_API mymath::MathBase* GetMathObject();
extern "C" MATH_API void DeleteMathObject(mymath::MathBase*);


#include <cmath>

#include "mathlib.h"

namespace mymath {

double mysin(double x) {
  return std::sin(x);
}

double MathLib::sin(double x) {
  return std::sin(x);
}

class MathImpl: public MathBase {
public:
  double sin(double x) override {
    return std::sin(x);
  }
};

} // namespace mymath

using namespace mymath;

MathBase* GetMathObject() {
  return dynamic_cast<MathBase*>(new MathImpl());
}

void DeleteMathObject(MathBase* ins) {
  delete ins;
}


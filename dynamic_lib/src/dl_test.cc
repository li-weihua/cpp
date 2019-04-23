#include <dlfcn.h>

#include <iostream>

#include "mathlib.h"

using namespace mymath;

int main() {

  void* handle = dlopen("./libmathlib.so", RTLD_LAZY);

  if (NULL == handle) {
    std::cout << "error in open library!" << std::endl;
    return -1;
  }

  typedef MathBase* (*GetMathObject_t)();

  GetMathObject_t GetMathObject = (GetMathObject_t)dlsym(handle, "GetMathObject");

  typedef void (*DeleteMathObject_t)(MathBase*);
  DeleteMathObject_t DeleteMathObject = (DeleteMathObject_t)dlsym(handle, "DeleteMathObject");

  MathBase* ins = GetMathObject();

  double x = 1.5;

  std::cout << "plugin: sin(x) = " << ins->sin(x) << std::endl;

  DeleteMathObject(ins);

  dlclose(handle);

  return 0;
}

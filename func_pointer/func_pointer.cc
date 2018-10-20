#include <iostream>

class TestClass {
 public:
  TestClass(int version) {
    version_ = version;
    MakeDispatch();
  }
  
  void ShowDispatch() {
    (this->*FuncDispatch)();
  }

 private:

  void MakeDispatch() {
    if (version_ == 0) {
      FuncDispatch = &TestClass::Func_SSE;
    } else if (version_ == 1) {
      FuncDispatch = &TestClass::Func_AVX;
    } else {
      FuncDispatch = NULL;
    }
  }

  void (TestClass::*FuncDispatch)();

  void Func_SSE() {
    std::cout << "calling SSE version" << std::endl;
  }

  void Func_AVX() {
    std::cout << "calling AVX version" << std::endl;
  }

 private:
  int version_;
};

int main(){

  TestClass t1(0);
  TestClass t2(1);

  t1.ShowDispatch();
  t2.ShowDispatch();

  return 0;
}

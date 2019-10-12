// Array class only movable, not copyable
class Array {
public:
  Array(): n_(0), data_(nullptr){}

  Array(int n):
    n_(n),
    data_(static_cast<float*>(malloc(sizeof(float) * n))) 
  { }

  Array(Array &&rhs) noexcept {
    data_ = rhs.data_;
    n_ = rhs.n_;
    rhs.data_ = nullptr;
    rhs.n_ = 0;
  }

  Array& operator=(Array &&rhs) noexcept{
    if (this != &rhs) {
      if (data_ != nullptr) {
        free(data_);
        data_ = nullptr;
        n_ = 0;
      }

      data_ = rhs.data_;
      n_ = rhs.n_;
      rhs.data_ = nullptr;
      rhs.n_ = 0;
    }
    return *this;
  }

  ~Array() {
    if (data_ != nullptr) {
      free(data_);
    }
  }

  // disable copy
  Array(const Array&) = delete;
  Array& operator=(const Array&) = delete;

  float& operator[](int index) {
    return data_[index];
  }

  const float& operator[](int index) const{
    return data_[index];
  }

  inline int Length() const {
    return n_;
  }

private:
  int n_;
  float *data_;
};




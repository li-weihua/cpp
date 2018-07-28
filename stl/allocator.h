#ifndef CPP_ALLOCATOR_H_
#define CPP_ALLOCATOR_H_
/*
template <>
class allocator<void>
{
public:
    typedef void*                                 pointer;
    typedef const void*                           const_pointer;
    typedef void                                  value_type;

    template <class _Up> struct rebind {typedef allocator<_Up> other;};
};

template <class T>
class allocator
{
public:
    typedef size_t                                size_type;
    typedef ptrdiff_t                             difference_type;
    typedef T*                                    pointer;
    typedef const T*                              const_pointer;
    typedef typename add_lvalue_reference<T>::type       reference;
    typedef typename add_lvalue_reference<const T>::type const_reference;
    typedef T                                     value_type;

    template <class U> struct rebind {typedef allocator<U> other;};

    allocator() noexcept;
    allocator(const allocator&) noexcept;
    template <class U> allocator(const allocator<U>&) noexcept;
    ~allocator();
    pointer address(reference x) const noexcept;
    const_pointer address(const_reference x) const noexcept;
    pointer allocate(size_type, allocator<void>::const_pointer hint = 0);
    void deallocate(pointer p, size_type n) noexcept;
    size_type max_size() const noexcept;
    template<class U, class... Args>
        void construct(U* p, Args&&... args);
    template <class U>
        void destroy(U* p);
};

template <class T, class U>
bool operator==(const allocator<T>&, const allocator<U>&) noexcept;

template <class T, class U>
bool operator!=(const allocator<T>&, const allocator<U>&) noexcept;
*/

#include <cstddef>
#include <utility>

namespace cpp {

template <class T>
class Allocator {
 public:
  typedef size_t        size_type;
  typedef T             value_type;
  typedef T*            pointer;
  typedef const T*      const_pointer;
  typedef T&            reference;
  typedef const T&      const_reference;
  typedef ptrdiff_t     difference_type; 

  Allocator() noexcept {}
  Allocator(const Allocator&) noexcept {}
  template <class U> Allocator(const Allocator<U>&) noexcept {}
  ~Allocator(){}

  pointer address(reference x) const noexcept {
    return &x;
  }

  const_pointer address(const_reference x) const noexcept {
    return &x;
  }

  pointer allocate(size_type n) {
    return static_cast<pointer>(::operator new(n*sizeof(T)));
  }

  void deallocate(pointer p, size_type n) noexcept {
    ::operator delete(p);
  }

  size_type max_size() const noexcept {
    return size_type(~0) / sizeof(T);
  }

  template <class U, class... Args>
  void construct(U *p, Args&&... args) {
    ::new((void*)p) U(std::forward<Args>(args)...);
  }

  void destroy(pointer p) {
    p->~T();
  }

};

template <class T, class U>
inline bool operator==(const Allocator<T>&, const Allocator<U>&) {
  return true;
}

template <class T, class U>
inline bool operator!=(const Allocator<T>&, const Allocator<U>&) {
  return false;
}

} // namespace cpp

#endif // CPP_ALLOCATOR_H_

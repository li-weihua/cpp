#ifndef CPP_ALLOCATOR_H_
#define CPP_ALLOCATOR_H_
/*
    memory synopsis

namespace std
{

template <class Ptr>
struct pointer_traits
{
    typedef Ptr pointer;
    typedef <details> element_type;
    typedef <details> difference_type;

    template <class U> using rebind = <details>;

    static pointer pointer_to(<details>);
};

template <class T>
struct pointer_traits<T*>
{
    typedef T* pointer;
    typedef T element_type;
    typedef ptrdiff_t difference_type;

    template <class U> using rebind = U*;

    static pointer pointer_to(<details>) noexcept;
};

template <class Alloc>
struct allocator_traits
{
    typedef Alloc                        allocator_type;
    typedef typename allocator_type::value_type
                                         value_type;

    typedef Alloc::pointer | value_type* pointer;
    typedef Alloc::const_pointer
          | pointer_traits<pointer>::rebind<const value_type>
                                         const_pointer;
    typedef Alloc::void_pointer
          | pointer_traits<pointer>::rebind<void>
                                         void_pointer;
    typedef Alloc::const_void_pointer
          | pointer_traits<pointer>::rebind<const void>
                                         const_void_pointer;
    typedef Alloc::difference_type
          | pointer_traits<pointer>::difference_type
                                         difference_type;
    typedef Alloc::size_type
          | make_unsigned<difference_type>::type
                                         size_type;
    typedef Alloc::propagate_on_container_copy_assignment
          | false_type                   propagate_on_container_copy_assignment;
    typedef Alloc::propagate_on_container_move_assignment
          | false_type                   propagate_on_container_move_assignment;
    typedef Alloc::propagate_on_container_swap
          | false_type                   propagate_on_container_swap;

    template <class T> using rebind_alloc  = Alloc::rebind<U>::other | Alloc<T, Args...>;
    template <class T> using rebind_traits = allocator_traits<rebind_alloc<T>>;

    static pointer allocate(allocator_type& a, size_type n);
    static pointer allocate(allocator_type& a, size_type n, const_void_pointer hint);

    static void deallocate(allocator_type& a, pointer p, size_type n) noexcept;

    template <class T, class... Args>
        static void construct(allocator_type& a, T* p, Args&&... args);

    template <class T>
        static void destroy(allocator_type& a, T* p);

    static size_type max_size(const allocator_type& a);

    static allocator_type
        select_on_container_copy_construction(const allocator_type& a);
};


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

}  // std
*/

#include <cstddef>
#include <utility>


namespace cpp {

namespace internel {

HasPointer

} // namespace internel

template <class Alloc>
struct AllocatorTraits {
  typedef Alloc               allocator_type;
  typedef typename allocator_type::value_type 
                              value_type;

  typedef Alloc::pointer | value_type* pointer;

  typedef Alloc::const_pointer
          | pointer_traits<pointer>::rebind<const value_type>
                                         const_pointer;
    typedef Alloc::void_pointer
          | pointer_traits<pointer>::rebind<void>
                                         void_pointer;
    typedef Alloc::const_void_pointer
          | pointer_traits<pointer>::rebind<const void>
                                         const_void_pointer;
    typedef Alloc::difference_type
          | pointer_traits<pointer>::difference_type
                                         difference_type;
    typedef Alloc::size_type
          | make_unsigned<difference_type>::type
                                         size_type;
    typedef Alloc::propagate_on_container_copy_assignment
          | false_type                   propagate_on_container_copy_assignment;
    typedef Alloc::propagate_on_container_move_assignment
          | false_type                   propagate_on_container_move_assignment;
    typedef Alloc::propagate_on_container_swap
          | false_type                   propagate_on_container_swap;

    template <class T> using rebind_alloc  = Alloc::rebind<U>::other | Alloc<T, Args...>;
    template <class T> using rebind_traits = allocator_traits<rebind_alloc<T>>;

    static pointer allocate(allocator_type& a, size_type n);
    static pointer allocate(allocator_type& a, size_type n, const_void_pointer hint);

    static void deallocate(allocator_type& a, pointer p, size_type n) noexcept;

    template <class T, class... Args>
        static void construct(allocator_type& a, T* p, Args&&... args);

    template <class T>
        static void destroy(allocator_type& a, T* p);

    static size_type max_size(const allocator_type& a);

    static allocator_type
        select_on_container_copy_construction(const allocator_type& a);
};


template <class T>
class Allocator {
 public:
  // common type define
  typedef size_t        size_type;
  typedef T             value_type;
  typedef T*            pointer;
  typedef const T*      const_pointer;
  typedef T&            reference;
  typedef const T&      const_reference;
  typedef ptrdiff_t     difference_type; 

  // constructors and destructor
  Allocator() noexcept {}
  Allocator(const Allocator&) noexcept {}
  template <class U> Allocator(const Allocator<U>&) noexcept {}
  ~Allocator(){}

  // member functions
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

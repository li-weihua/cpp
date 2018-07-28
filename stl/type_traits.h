#ifndef CPP_TYPE_TRAITS_H_
#define CPP_TYPE_TRAITS_H_

namespace cpp {

// std::integral_constant
template <class T, T v>
struct IntegralConstant {
  static constexpr T value = v;

  typedef T value_type;
  typedef IntegralConstant type;

  constexpr operator value_type() const noexcept { return value; }
  // c++ 14
#if CPP_VER >= 14
  constexpr operator ()() const noexcept { return value; }
#endif
};

// std::true_type and std::false_type
typedef IntegralConstant<bool, true>  TrueType;
typedef IntegralConstant<bool, false> FalseType;

// std::is_same
template< class T, class U >
struct IsSame : public FalseType {
};

template< class T>
struct IsSame<T, T> : public FalseType {
};

// is_same no dependent
template< class T, class U >
struct IsSameType {
  static constexpr bool value = false;
};

template< class T>
struct IsSameType<T, T> {
  static constexpr bool value = true;
};

// std::enable_if
template<bool B, class T = void>
struct EnableIf {};
 
template<class T>
struct EnableIf<true, T> { typedef T type; };

// std::conditional
template<bool B, class T, class F>
struct Conditional { typedef T type; };
 
template<class T, class F>
struct Conditional<false, T, F> { typedef F type; };

// std::is_const
template <typename T>
struct IsConst : public FalseType {
};

template <typename T>
struct IsConst<T const> : public TrueType {
};

// std::is_volatile
template <typename T>
struct IsVolatile : public FalseType {
};

template <typename T>
struct IsVolatile<T volatile> : public TrueType {
};

// std::remove_const
template <class T>
struct RemoveConst {
  typedef T type;
};

template <class T>
struct RemoveConst<const T>{
  typedef T type;
};


// std::remove_volatile
template <class T>
struct RemoveVolatile {
  typedef T type;
};

template <class T>
struct RemoveVolatile<volatile T>{
  typedef T type;
};

// std::remove_cv
template <class T>
struct RemoveCV {
  typedef typename RemoveVolatile<typename RemoveConst<T>::type>::type type;
};


} // namespace cpp

#endif

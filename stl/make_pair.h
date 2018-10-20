#ifndef CPP_PAIR_H_
#define CPP_PAIR_H_

namespace cpp {

/*
template <class T1, class T2>
struct pair
{
    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;

    pair(const pair&) = default;
    pair(pair&&) = default;
    constexpr pair();
    pair(const T1& x, const T2& y);
    template <class U, class V> pair(U&& x, V&& y);
    template <class U, class V> pair(const pair<U, V>& p);
    template <class U, class V> pair(pair<U, V>&& p);
    template <class... Args1, class... Args2>
        pair(piecewise_construct_t, tuple<Args1...> first_args,
             tuple<Args2...> second_args);

    template <class U, class V> pair& operator=(const pair<U, V>& p);
    pair& operator=(pair&& p) noexcept(is_nothrow_move_assignable<T1>::value &&
                                       is_nothrow_move_assignable<T2>::value);
    template <class U, class V> pair& operator=(pair<U, V>&& p);

    void swap(pair& p) noexcept(noexcept(swap(first, p.first)) &&
                                noexcept(swap(second, p.second)));
};

template <class T1, class T2> bool operator==(const pair<T1,T2>&, const pair<T1,T2>&);
template <class T1, class T2> bool operator!=(const pair<T1,T2>&, const pair<T1,T2>&);
template <class T1, class T2> bool operator< (const pair<T1,T2>&, const pair<T1,T2>&);
template <class T1, class T2> bool operator> (const pair<T1,T2>&, const pair<T1,T2>&);
template <class T1, class T2> bool operator>=(const pair<T1,T2>&, const pair<T1,T2>&);
template <class T1, class T2> bool operator<=(const pair<T1,T2>&, const pair<T1,T2>&);

template <class T1, class T2> pair<V1, V2> make_pair(T1&&, T2&&);
template <class T1, class T2>
void
swap(pair<T1, T2>& x, pair<T1, T2>& y) noexcept(noexcept(x.swap(y)));
*/

template <class T1, class T2>
struct Pair {
 public:
  typedef T1 first_type;
  typedef T2 second_type;

  T1 first;
  T2 second;

  constexpr Pair(): first(), second() {}
  Pair(const T1& x, const T2& y): first(x), second(y) {}

  // copy constructor
  Pair(const Pair& p): first(p.first), second(p.second) {}

  // copy constructor template
  template <class U, class V>
  pair(const pair<U, V> &p): first(p.first), second(p.second) {}

  // copy-assignment operator
  Pair& operator=(const Pair&) = default;

  pair(pair&&) = default;

};


// std::make_pair

} // namespace cpp

#endif // CPP_PAIR_H_

// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_MATH_LYNEL_VECTOROPS_HPP
#define TYBL_MATH_LYNEL_VECTOROPS_HPP

#include <algorithm>
#include <numeric>

namespace tybl::math::lynel {

template <typename T, size_t N>
auto operator+(vector<T,N> const& l, vector<T,N> const& r) -> vector<T,N> {
  vector<T,N> result;
  ::std::transform(l.begin(), l.end(), r.begin(), result.begin(), ::std::plus());
  return result;
}

template <typename T, size_t N>
auto operator*(T l, vector<T,N> r) -> vector<T,N> {
  for (auto& e : r) { e *= l; }
  return r;
}

template <typename T, size_t N>
constexpr auto operator*(vector<T,N> const& l, T r) -> vector<T,N> {
  return r * l;
}

template <typename T, size_t M>
constexpr auto dot_product(vector<T,M> const& l, vector<T,M> const& r) -> T {
  return ::std::inner_product(l.begin(), l.end(), r.begin(), 0.0);
}

} // namespace tybl::math::lynel

#endif // TYBL_MATH_LYNEL_VECTOROPS_HPP

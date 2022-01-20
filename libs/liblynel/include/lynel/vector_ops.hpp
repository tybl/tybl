// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LYNEL_VECTOROPS_HPP
#define TYBL_LYNEL_VECTOROPS_HPP

#include <algorithm>
#include <cmath>
#include <numeric>

namespace tybl::lynel {

template <typename T, size_t N>
auto operator+(vector<T, N> const& l, vector<T, N> const& r) -> vector<T, N> {
  vector<T, N> result;
  ::std::transform(l.begin(), l.end(), r.begin(), result.begin(), ::std::plus());
  return result;
}

template <typename T, size_t N>
auto operator*(T l, vector<T, N> r) -> vector<T, N> {
  for (auto& e : r) {
    e *= l;
  }
  return r;
}

template <typename T, size_t N>
constexpr auto operator*(vector<T, N> const& l, T r) -> vector<T, N> {
  return r * l;
}

template <typename T, size_t N>
auto operator-(vector<T, N> const& v) -> vector<T, N> {
  return static_cast<T>(-1) * v;
}

template <typename T, size_t N>
constexpr auto dot_product(vector<T, N> const& l, vector<T, N> const& r) -> T {
  return ::std::inner_product(l.begin(), l.end(), r.begin(), 0.0);
}

template <typename T, size_t N>
constexpr auto magnitude(vector<T, N> const& v) -> T {
  return ::std::sqrt(dot_product(v, v));
}

template <typename T>
constexpr auto cross_product(vector<T, 3> const& l, vector<T, 3> const& r) -> vector<T, 3> {
  return vector<T, 3>{l[1] * r[2] - l[2] * r[1], l[2] * r[0] - l[0] * r[2], l[0] * r[1] - l[1] * r[0]};
}

template <typename T, size_t N>
constexpr auto projection(vector<T, N> const& l, vector<T, N> const& r) -> vector<T, N> {
  return (dot_product(l, r) / dot_product(r, r)) * r;
}

template <typename T, size_t N>
constexpr auto rejection(vector<T, N> const& l, vector<T, N> const& r) -> vector<T, N> {
  return l - projection(l, r);
}

} // namespace tybl::lynel

#endif // TYBL_LYNEL_VECTOROPS_HPP

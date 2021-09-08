// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LINAL_CVEC4_HPP
#define TYBL_LINAL_CVEC4_HPP

#include "linal/basic_matrix.hpp"

namespace tybl::linal {

// Rank 4 Column Vector specialization
template <typename T>
struct basic_matrix<T,4,1> {

  // types:
  using value_type = T;

  // member variables:
  value_type x;
  value_type y;
  value_type z;
  value_type w;

  constexpr auto operator==(basic_matrix const& v) const -> bool {
    return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
  }

  constexpr auto operator+=(basic_matrix const& v) -> cvec4<T>& {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }

  constexpr auto operator-=(basic_matrix const& v) -> cvec4<T>& {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
  }

  constexpr auto operator*=(value_type s) -> cvec4<T>& {
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
  }

  constexpr auto operator/=(value_type s) -> cvec4<T>& {
    x /= s;
    y /= s;
    z /= s;
    w /= s;
    return *this;
  }

  constexpr auto dot(basic_matrix const& v) const -> value_type {
    return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
  }

};

template <typename T>
constexpr auto operator*(T s, cvec4<T> v) -> cvec4<T> {
  return v *= s;
}

template <typename T>
constexpr auto add(cvec4<T> l, cvec4<T> const& r) -> cvec4<T> {
  return l += r;
}

template <typename T>
constexpr auto subtract(cvec4<T> l, cvec4<T> const& r) -> cvec4<T> {
  return l -= r;
}

} // namespace tybl::linal

#endif // TYBL_LINAL_CVEC4_HPP

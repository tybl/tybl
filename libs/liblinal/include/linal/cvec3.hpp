// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LINAL_CVEC3_HPP
#define TYBL_LINAL_CVEC3_HPP

#include "linal/basic_matrix.hpp"

namespace tybl::linal {

// Rank 3 Column Vector specialization
template <typename T>
struct basic_matrix<T,3,1> {

  // types:
  using value_type = T;

  value_type x;
  value_type y;
  value_type z;

  constexpr auto operator==(basic_matrix const& v) const -> bool {
    return (x == v.x) && (y == v.y) && (z == v.z);
  }

  constexpr auto operator+=(basic_matrix const& v) -> cvec3<T>& {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  constexpr auto operator-=(basic_matrix const& v) -> cvec3<T>& {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  constexpr auto operator*=(value_type s) -> cvec3<T>& {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }

  constexpr auto operator/=(value_type s) -> cvec3<T>& {
    x /= s;
    y /= s;
    z /= s;
    return *this;
  }

  constexpr auto dot(basic_matrix const& v) const -> value_type {
    return (x * v.x) + (y * v.y) + (z * v.z);
  }

};

template <typename T>
constexpr auto operator*(T s, cvec3<T> v) -> cvec3<T> {
  return v *= s;
}

template <typename T>
constexpr auto add(cvec3<T> l, cvec3<T> const& r) -> cvec3<T> {
  return l += r;
}

template <typename T>
constexpr auto subtract(cvec3<T> l, cvec3<T> const& r) -> cvec3<T> {
  return l -= r;
}

} // namespace tybl::linal

#endif // TYBL_LINAL_CVEC3_HPP

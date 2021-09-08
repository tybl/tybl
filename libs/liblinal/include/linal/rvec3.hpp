// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LINAL_RVEC3_HPP
#define TYBL_LINAL_RVEC3_HPP

#include "linal/basic_matrix.hpp"

namespace tybl::linal {

// Rank 3 Row Vector specialization
template <typename T>
struct basic_matrix<T,1,3> {

  // types:
  using value_type = T;

  value_type x;
  value_type y;
  value_type z;

  constexpr auto operator==(basic_matrix const& v) const -> bool {
    return (x == v.x) && (y == v.y) && (z == v.z);
  }

  constexpr auto operator+=(basic_matrix const& v) -> rvec3<T>& {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  constexpr auto operator-=(basic_matrix const& v) -> rvec3<T>& {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  constexpr auto operator*=(value_type s) -> rvec3<T>& {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }

  constexpr auto operator/=(value_type s) -> rvec3<T>& {
    x /= s;
    y /= s;
    z /= s;
    return *this;
  }

};

template <typename T>
constexpr auto operator*(T s, rvec3<T> v) -> rvec3<T> {
  return v *= s;
}

template <typename T>
constexpr auto add(rvec3<T> l, rvec3<T> const& r) -> rvec3<T> {
  return l += r;
}

template <typename T>
constexpr auto subtract(rvec3<T> l, rvec3<T> const& r) -> rvec3<T> {
  return l -= r;
}

} // namespace tybl::linal

#endif // TYBL_LINAL_RVEC3_HPP

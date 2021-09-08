// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LINAL_RVEC4_HPP
#define TYBL_LINAL_RVEC4_HPP

#include "linal/basic_matrix.hpp"

namespace tybl::linal {

// Rank 4 Row Vector specialization
template <typename T>
struct basic_matrix<T,1,4> {

  // types:
  using value_type = T;

  value_type x;
  value_type y;
  value_type z;
  value_type w;

  constexpr auto operator==(basic_matrix const& v) const -> bool {
    return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
  }

  constexpr auto operator+=(basic_matrix const& v) -> rvec4<T>& {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }

  constexpr auto operator-=(basic_matrix const& v) -> rvec4<T>& {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
  }

  constexpr auto operator*=(value_type s) -> rvec4<T>& {
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
  }

  constexpr auto operator/=(value_type s) -> rvec4<T>& {
    x /= s;
    y /= s;
    z /= s;
    w /= s;
    return *this;
  }

};

template <typename T>
constexpr auto add(rvec4<T> l, rvec4<T> const& r) -> rvec4<T> {
  l.x += r.x;
  l.y += r.y;
  l.z += r.z;
  l.w += r.w;
  return l;
}

template <typename T>
constexpr auto subtract(rvec4<T> l, rvec4<T> const& r) -> rvec4<T> {
  l.x -= r.x;
  l.y -= r.y;
  l.z -= r.z;
  l.w -= r.w;
  return l;
}

} // namespace tybl::linal

#endif // TYBL_LINAL_RVEC4_HPP

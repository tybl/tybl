// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LINAL_CVEC2_HPP
#define TYBL_LINAL_CVEC2_HPP

#include "linal/basic_matrix.hpp"

namespace tybl::linal {

// Rank 2 Column Vector specialization
template <typename T>
struct basic_matrix<T,2,1> {

  // types:
  using value_type = T;

  value_type x;
  value_type y;

  constexpr auto operator==(basic_matrix const& v) const -> bool {
    return (x == v.x) && (y == v.y);
  }

  constexpr auto operator+=(basic_matrix const& v) -> cvec2<T>& {
    x += v.x;
    y += v.y;
    return *this;
  }

  constexpr auto operator-=(basic_matrix const& v) -> cvec2<T>& {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  constexpr auto operator*=(value_type s) -> cvec2<T>& {
    x *= s;
    y *= s;
    return *this;
  }

  constexpr auto operator/=(value_type s) -> cvec2<T>& {
    x /= s;
    y /= s;
    return *this;
  }

  constexpr auto dot(basic_matrix const& v) const -> value_type {
    return (x * v.x) + (y * v.y);
  }

};

template <typename T>
constexpr auto add(cvec2<T> l, cvec2<T> const& r) -> cvec2<T> {
  return l += r;
}

template <typename T>
constexpr auto subtract(cvec2<T> l, cvec2<T> const& r) -> cvec2<T> {
  return l -= r;
}

} // namespace tybl::linal

#endif // TYBL_LINAL_CVEC2_HPP

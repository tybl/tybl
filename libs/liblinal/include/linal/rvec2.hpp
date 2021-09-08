// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LINAL_RVEC2_HPP
#define TYBL_LINAL_RVEC2_HPP

#include "linal/basic_matrix.hpp"

namespace tybl::linal {

// Rank 2 Row Vector specialization
template <typename T>
struct basic_matrix<T,1,2> {

  // types:
  using value_type = T;

  value_type x;
  value_type y;

  constexpr auto operator==(basic_matrix const& v) const -> bool {
    return (x == v.x) && (y == v.y);
  }

  constexpr auto operator+=(basic_matrix const& v) -> rvec2<T>& {
    x += v.x;
    y += v.y;
    return *this;
  }

  constexpr auto operator-=(basic_matrix const& v) -> rvec2<T>& {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  constexpr auto operator*=(value_type s) -> rvec2<T>& {
    x *= s;
    y *= s;
    return *this;
  }

  constexpr auto operator/=(value_type s) -> rvec2<T>& {
    x /= s;
    y /= s;
    return *this;
  }

};

template <typename T>
constexpr auto add(rvec2<T> l, rvec2<T> const& r) -> rvec2<T> {
  return l += r;
}

template <typename T>
constexpr auto subtract(rvec2<T> l, rvec2<T> const& r) -> rvec2<T> {
  return l -= r;
}

} // namespace tybl::linal

#endif // TYBL_LINAL_RVEC2_HPP

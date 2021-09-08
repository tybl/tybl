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
};

template <typename T>
constexpr auto add(rvec2<T> l, rvec2<T> const& r) -> rvec2<T> {
  l.x += r.x;
  l.y += r.y;
  return l;
}

template <typename T>
constexpr auto subtract(rvec2<T> l, rvec2<T> const& r) -> rvec2<T> {
  l.x -= r.x;
  l.y -= r.y;
  return l;
}

} // namespace tybl::linal

#endif // TYBL_LINAL_RVEC2_HPP

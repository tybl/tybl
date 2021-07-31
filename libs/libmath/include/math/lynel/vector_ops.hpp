// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_MATH_LYNEL_VECTOROPS_HPP
#define TYBL_MATH_LYNEL_VECTOROPS_HPP

#include <algorithm>

namespace tybl::math::lynel {

template <typename T, size_t N>
auto operator+(vector<T,N> const& l, vector<T,N> const& r) -> vector<T,N> {
  vector<T,N> result;
  ::std::transform(l.begin(), l.end(), r.begin(), result.begin(), ::std::plus());
  return result;
}

} // namespace tybl::math::lynel

#endif // TYBL_MATH_LYNEL_VECTOROPS_HPP

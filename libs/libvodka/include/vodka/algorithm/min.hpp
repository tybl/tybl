// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_ALGORITHM_MIN_HPP
#define TYBL_VODKA_ALGORITHM_MIN_HPP

#include "vodka/functional/less.hpp"

// Relevant links:
// cppreference: https://en.cppreference.com/w/cpp/algorithm/min

namespace tybl::vodka {

template<typename T, typename Compare> 
[[nodiscard]] constexpr auto
min(T const& lhs, T const& rhs, Compare comp) -> T const& {
  return comp(lhs, rhs) ? lhs : rhs;
}

template <typename T>
[[nodiscard]] constexpr auto
min(T const& lhs, T const& rhs) -> T const& {
  return min(lhs, rhs, less());
}

} // namespace tybl::vodka

#endif // TYBL_VODKA_ALGORITHM_MIN_HPP

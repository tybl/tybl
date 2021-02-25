// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_ALGORITHM_MAX_HPP
#define TYBL_VODKA_ALGORITHM_MAX_HPP

#include "vodka/functional/less.hpp"

// Relevant links:
// cppreference: https://en.cppreference.com/w/cpp/algorithm/max

namespace tybl::vodka {

template<typename T, typename Compare> 
[[nodiscard]] constexpr auto
max(T const& lhs, T const& rhs, Compare comp) -> T const& {
  return comp(lhs, rhs) ? rhs : lhs;
}

template <typename T>
[[nodiscard]] constexpr auto
max(T const& lhs, T const& rhs) -> T const& {
  return max(lhs, rhs, less());
}

} // namespace tybl::vodka

#endif // TYBL_VODKA_ALGORITHM_MAX_HPP

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
min(T const& p_lhs, T const& p_rhs, Compare p_comp) -> T const& {
  return p_comp(p_lhs, p_rhs) ? p_lhs : p_rhs;
}

template <typename T>
[[nodiscard]] constexpr auto
min(T const& p_lhs, T const& p_rhs) -> T const& {
  return min(p_lhs, p_rhs, less());
}

} // namespace tybl::vodka

#endif // TYBL_VODKA_ALGORITHM_MIN_HPP

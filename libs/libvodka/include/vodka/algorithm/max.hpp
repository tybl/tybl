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
max(T const& p_lhs, T const& p_rhs, Compare p_comp) -> T const& {
  return p_comp(p_lhs, p_rhs) ? p_rhs : p_lhs;
}

template <typename T>
[[nodiscard]] constexpr auto
max(T const& p_lhs, T const& p_rhs) -> T const& {
  return max(p_lhs, p_rhs, less());
}

} // namespace tybl::vodka

#endif // TYBL_VODKA_ALGORITHM_MAX_HPP

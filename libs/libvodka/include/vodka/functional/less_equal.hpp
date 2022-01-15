// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_FUNCTIONAL_LESSEQUAL_HPP
#define TYBL_VODKA_FUNCTIONAL_LESSEQUAL_HPP

#include "vodka/utility/forward.hpp"

// Relevant links:

namespace tybl::vodka {

template <typename T = void>
struct less_equal {

  [[nodiscard]] constexpr auto
  operator()(T const& p_lhs, T const& p_rhs) const -> bool {
    return p_lhs <= p_rhs;
  }

};

template <>
struct less_equal<void> {

  using is_transparent = void;

  template <typename TypeL, typename TypeR>
  [[nodiscard]] constexpr auto
  operator()(TypeL&& p_lhs, TypeR&& p_rhs) const
    noexcept(noexcept(forward<TypeL>(p_lhs) <= forward<TypeR>(p_rhs)))
    ->       decltype(forward<TypeL>(p_lhs) <= forward<TypeR>(p_rhs))
  {
    return            forward<TypeL>(p_lhs) <= forward<TypeR>(p_rhs);
  }

};

} // namespace tybl::vodka

#endif // TYBL_VODKA_FUNCTIONAL_LESSEQUAL_HPP

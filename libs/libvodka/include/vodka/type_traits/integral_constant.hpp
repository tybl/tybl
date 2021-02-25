// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_TYPETRAITS_INTEGRALCONSTANT_HPP
#define TYBL_VODKA_TYPETRAITS_INTEGRALCONSTANT_HPP

namespace tybl::vodka {

template <typename T, T V>
struct integral_constant {

  using value_type = T;
  using type = integral_constant;

  static constexpr value_type value = V;

  constexpr operator value_type() const noexcept {
    return value;
  }

  [[nodiscard]]
  constexpr auto
  operator()() const noexcept -> value_type {
    return value;
  }

};

} // namespace tybl::vodka

#endif // TYBL_VODKA_TYPETRAITS_INTEGRALCONSTANT_HPP

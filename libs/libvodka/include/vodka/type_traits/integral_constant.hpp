// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_TYPETRAITS_INTEGRALCONSTANT_HPP
#define TYBL_VODKA_TYPETRAITS_INTEGRALCONSTANT_HPP

namespace tybl::vodka {

template <typename Type, Type Value>
struct integral_constant {

  using value_type = Type;
  using type = integral_constant;

  static constexpr value_type value = Value;

  constexpr explicit operator value_type() const noexcept { return value; }

  [[nodiscard]] constexpr auto operator()() const noexcept -> value_type { return value; }
};

} // namespace tybl::vodka

#endif // TYBL_VODKA_TYPETRAITS_INTEGRALCONSTANT_HPP

// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_NUMERIC_GCD_HPP
#define TYBL_VODKA_NUMERIC_GCD_HPP

#include "vodka/type_traits/is_bool.hpp"

namespace tybl::vodka {

template<class TypeM, class TypeN>
[[nodiscard]] constexpr auto
gcd(TypeM m, TypeN n) -> common_type_t<TypeM, TypeN> {
  static_assert((is_integral_v<TypeM> && is_integral_v<TypeN>), "Arguments to gcd must be integer types");
  static_assert(!(is_bool_v<TypeM> || is_bool_v<TypeN>), "Arguments to gcd cannot be bool" );

  using CommonType = common_type_t<TypeM, TypeN>;
  using CommonUnsignedType = make_unsigned_t<CommonType>;

  return static_cast<CommonType>(gcd(static_cast<CommonUnsignedType>(__ct_abs<CommonType, TypeM>()(m)), static_cast<CommonUnsignedType>(__ct_abs<CommonType, TypeN>()(n))));
}

template<typename Type>
[[nodiscard]] constexpr auto
gcd<Type, Type>(Type m, Type n) -> Type {
  static_assert((!is_signed_v<Type>), "");
  return n == 0 ? m : impl_gcd<Type>(n, m % n);
}

} // namespace tybl::vodka

#endif // TYBL_VODKA_NUMERIC_GCD_HPP

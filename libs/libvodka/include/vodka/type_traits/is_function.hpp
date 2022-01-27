// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef _TYBL__VODKA__TYPE_TRAITS__IS_FUNCTION__HPP_
#define _TYBL__VODKA__TYPE_TRAITS__IS_FUNCTION__HPP_

#include <vodka/type_traits/integral_constant.hpp>
#include <vodka/type_traits/is_const.hpp>
#include <vodka/type_traits/is_reference.hpp>

namespace tybl::vodka {

template <typename MaybeFunctionType>
struct is_function
  : ::tybl::vodka::integral_constant<bool, !::tybl::vodka::is_const_v<const MaybeFunctionType> &&
                                               !::tybl::vodka::is_reference_v<MaybeFunctionType>> {};

template <typename MaybeFunctionType>
constexpr bool is_function_v = is_function<MaybeFunctionType>::value;

} // namespace tybl::vodka

#endif // _TYBL__VODKA__TYPE_TRAITS__IS_FUNCTION__HPP_

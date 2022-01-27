// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef _TYBL__VODKA__TYPE_TRAITS__IS_CONST__HPP_
#define _TYBL__VODKA__TYPE_TRAITS__IS_CONST__HPP_

#include <vodka/type_traits/false_type.hpp>
#include <vodka/type_traits/true_type.hpp>

namespace tybl::vodka {

template <typename MaybeConstType>
struct is_const : ::tybl::vodka::false_type {};

template <typename MaybeConstType>
struct is_const<const MaybeConstType> : ::tybl::vodka::true_type {};

template <typename MaybeConstType>
constexpr bool is_const_v = is_const<MaybeConstType>::value;

} // namespace tybl::vodka

#endif // _TYBL__VODKA__TYPE_TRAITS__IS_CONST__HPP_

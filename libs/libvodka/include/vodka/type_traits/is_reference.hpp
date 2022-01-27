// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef _TYBL__VODKA__TYPE_TRAITS__IS_REFERENCE__HPP_
#define _TYBL__VODKA__TYPE_TRAITS__IS_REFERENCE__HPP_

#include <vodka/type_traits/false_type.hpp>
#include <vodka/type_traits/true_type.hpp>

namespace tybl::vodka {

template <typename MaybeReferenceType>
struct is_reference : ::tybl::vodka::false_type {};

template <typename MaybeReferenceType>
struct is_reference<MaybeReferenceType&> : ::tybl::vodka::true_type {};

template <typename MaybeReferenceType>
struct is_reference<MaybeReferenceType&&> : ::tybl::vodka::true_type {};

template <typename MaybeReferenceType>
constexpr bool is_reference_v = is_reference<MaybeReferenceType>::value;

} // namespace tybl::vodka

#endif // _TYBL__VODKA__TYPE_TRAITS__IS_REFERENCE__HPP_

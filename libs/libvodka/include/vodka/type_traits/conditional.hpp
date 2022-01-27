// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef _TYBL__VODKA__TYPE_TRAITS__CONDITIONAL__HPP_
#define _TYBL__VODKA__TYPE_TRAITS__CONDITIONAL__HPP_

namespace tybl::vodka {

template <bool Condition, typename TrueType, typename FalseType>
struct conditional {
  using type = TrueType;
};

template <typename TrueType, typename FalseType>
struct conditional<false, TrueType, FalseType> {
  using type = FalseType;
};

template <bool Condition, typename TrueType, typename FalseType>
using conditional_t = typename conditional<Condition, TrueType, FalseType>::type;

} // namespace tybl::vodka

#endif // _TYBL__VODKA__TYPE_TRAITS__CONDITIONAL__HPP_

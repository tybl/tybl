// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef _TYBL__VODKA__ALGORITHM__INNER_PRODUCT__HPP_
#define _TYBL__VODKA__ALGORITHM__INNER_PRODUCT__HPP_

#include "vodka/utility/move.hpp"

namespace tybl::vodka {

template <typename Iter1, typename Iter2, typename Type>
constexpr Type inner_product(Iter1 p_range1_begin, Iter1 p_range1_end, Iter2 p_range2_begin, Type p_initial_value) {
  for (; p_range1_begin != p_range1_end; ++p_range1_begin, ++p_range2_begin) {
    p_initial_value = ::tybl::vodka::move(p_initial_value) + *p_range1_begin * *p_range2_begin;
  }
  return p_initial_value;
} // inner_product()

} // namespace tybl::vodka

#endif // _TYBL__VODKA__ALGORITHM__INNER_PRODUCT__HPP_
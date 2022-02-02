// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_ALGORITHM_ALLOF_HPP
#define TYBL_VODKA_ALGORITHM_ALLOF_HPP

#include "vodka/algorithm/find_if_not.hpp"

namespace tybl::vodka {

template <typename Iter, typename Pred>
constexpr auto all_of(Iter p_range_begin, Iter p_range_end, Pred p_predicate) -> bool {
  return (::tybl::vodka::find_if_not(p_range_begin, p_range_end, p_predicate) == p_range_end);
}

} // namespace tybl::vodka

#endif // TYBL_VODKA_ALGORITHM_ALLOF_HPP

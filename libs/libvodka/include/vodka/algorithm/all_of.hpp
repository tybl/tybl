// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_ALGORITHM_ALLOF_HPP
#define TYBL_VODKA_ALGORITHM_ALLOF_HPP

#include "vodka/algorithm/find_if_not.hpp"

namespace tybl::vodka {

template <typename Iter, typename Pred>
constexpr bool all_of(Iter first, Iter last, Pred p) {
  return (::tybl::vodka::find_if_not(first, last, p) == last);
}

} // namespace tybl::vodka

#endif // TYBL_VODKA_ALGORITHM_ALLOF_HPP

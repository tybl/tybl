// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_ALGORITHM_FINDIFNOT_HPP
#define TYBL_VODKA_ALGORITHM_FINDIFNOT_HPP

namespace tybl::vodka {

template <typename Iter, typename Pred>
constexpr auto find_if_not(Iter first, Iter last, Pred p) -> Iter {
  for (; first != last; ++first) {
    if (!p(*first)) {
      return first;
    }
  }
  return last;
} // find_if_not()

} // namespace tybl::vodka

#endif // TYBL_VODKA_ALGORITHM_FINDIFNOT_HPP

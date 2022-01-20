// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_ALGORITHM_EQUAL_HPP
#define TYBL_VODKA_ALGORITHM_EQUAL_HPP

namespace tybl::vodka {

template <class Iter1, class Iter2>
bool equal(Iter1 first1, Iter1 last1, Iter2 first2) {
  for (; first1 != last1; ++first1, ++first2) {
    if (!(*first1 == *first2)) {
      return false;
    }
  }
  return true;
}

} // namespace tybl::vodka

#endif // TYBL_VODKA_ALGORITHM_EQUAL_HPP

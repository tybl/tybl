// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef _TYBL__VODKA__ALGORITHM__ARE_EQUAL__HPP_
#define _TYBL__VODKA__ALGORITHM__ARE_EQUAL__HPP_

namespace tybl::vodka {

template <class Range1Iterator, class Range2Iterator>
bool are_equal(Range1Iterator p_range1_begin, Range1Iterator p_range1_end, Range2Iterator p_range2_begin) {
  for (; p_range1_begin != p_range1_end; ++p_range1_begin, ++p_range2_begin) {
    if (!(*p_range1_begin == *p_range2_begin)) {
      return false;
    }
  }
  return true;
}

} // namespace tybl::vodka

#endif // _TYBL__VODKA__ALGORITHM__ARE_EQUAL__HPP_

// License: The Unlicense (https://unlicense.org)
#ifndef TBL_MATH_NEXTPOWEROFTWO_HPP
#define TBL_MATH_NEXTPOWEROFTWO_HPP

#include <cstddef>
#include <limits>
#include <type_traits>

namespace tybl::math {

template <typename TYPE>
TYPE next_power_of_two(TYPE number) {
  static_assert(std::is_integral<TYPE>::value, "next_power_of_two(): cannot use bit shifts on floating point numbers");
  TYPE result = number - 1;
  for (size_t i = 1; i < std::numeric_limits<TYPE>::digits; i <<= 1) {
    result |= result >> i;
  }
  return result + 1;
}

// The above algorithm doesn't work for booleans.
// Since powers of two aren't defined in a boolean, it would be easiest to
// simply always return 0
template <>
bool next_power_of_two<bool>(bool /*number*/) { return false; }

} // namespace tybl::math

#endif // TBL_MATH_NEXTPOWEROFTWO_HPP

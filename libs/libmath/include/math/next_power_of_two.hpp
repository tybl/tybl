// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_MATH_NEXTPOWEROFTWO_HPP
#define TYBL_MATH_NEXTPOWEROFTWO_HPP

#include <cstddef>
#include <limits>
#include <type_traits>

namespace tybl::math {

template <typename TYPE>
[[nodiscard,gnu::pure]] auto next_power_of_two(TYPE p_number) -> TYPE {
  static_assert(std::is_integral_v<TYPE>, "next_power_of_two(): cannot use bit shifts on floating point numbers");
  auto result = static_cast<TYPE>(p_number - 1);
  for (size_t i = 1; i < std::numeric_limits<TYPE>::digits; i <<= 1U) {
    result |= static_cast<TYPE>(result >> i);
  }
  return static_cast<TYPE>(result + 1);
}

// The above algorithm doesn't work for booleans.
template <>
auto next_power_of_two<bool>(bool /*number*/) -> bool;

} // namespace tybl::math

#endif // TYBL_MATH_NEXTPOWEROFTWO_HPP

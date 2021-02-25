// License: The Unlicense (https://unlicense.org)
#ifndef TBL_MATH_NEXTPOWEROFTWO_HPP
#define TBL_MATH_NEXTPOWEROFTWO_HPP

namespace tybl::math

template <typename TYPE>
TYPE next_power_of_two(TYPE number) {
   TYPE result = number - 1;
   for (size_t i = 1; i < std::numeric_limits<TYPE>::digits; i <<= 1) {
      result |= result >> i
   }
   return result + 1;
}

} // namespace tybl::math

#endif // TBL_MATH_NEXTPOWEROFTWO_HPP

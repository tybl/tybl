// License: The Unlicense (https://unlicense.org)
#ifndef MATH_FIXEDPOINT_HPP
#define MATH_FIXEDPOINT_HPP

#include "math/pow10.hpp"

#include <cstdint>
#include <iosfwd>
#include <ratio>

namespace tybl::math {

template <typename RATIO>
struct fixed_point_t {

   using ratio = RATIO;

   constexpr fixed_point_t()
      : m_value() {}

   explicit constexpr fixed_point_t(double value)
      : m_value(static_cast<int64_t>(value * ratio::den) / ratio::num) {}

   constexpr fixed_point_t& operator+=(const fixed_point_t& other) {
      m_value += other.m_value;
      return *this;
   }

   constexpr fixed_point_t& operator-=(const fixed_point_t& other) {
      m_value -= other.m_value;
      return *this;
   }

   constexpr int64_t whole_number() const {
      return (m_value * ratio::num) / ratio::den;
   }

   int64_t& significand() {
      return m_value;
   }

   constexpr int64_t significand() const {
      return m_value;
   }

   struct rational_t {

      constexpr rational_t(int64_t numerator, uint64_t denominator)
         : m_numerator(numerator)
         , m_denominator(denominator) {}

      int64_t m_numerator;
      uint64_t m_denominator;
   };

   constexpr rational_t fraction() const {
      return rational_t((m_value * ratio::num) % ratio::den, ratio::den);
   }

private:
   int64_t m_value;
}; // struct fixed_point_t

template <typename RATIO>
std::ostream& operator<<(std::ostream& out, const fixed_point_t<RATIO>& fp) {
   if /*constexpr*/ (RATIO::den == 1) {
      return out << fp.whole_number();
   } else if /*constexpr*/ ((RATIO::den % 10) == 0) {
      // TODO(tblyons): Set width of fractional component
      return out << fp.whole_number() << '.' << fp.fraction().m_numerator;
   } else {
      return out << fp.whole_number() << ' ' << fp.fraction().m_numerator << '/' << fp.fraction().m_denominator;
   }
}

} // namespace tybl::math

#endif // MATH_FIXEDPOINT_HPP

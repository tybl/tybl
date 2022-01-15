// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_MATH_FIXEDPOINT_HPP
#define TYBL_MATH_FIXEDPOINT_HPP

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

   explicit constexpr fixed_point_t(double p_value)
      : m_value(static_cast<int64_t>(p_value * ratio::den) / ratio::num) {}

   constexpr fixed_point_t& operator+=(const fixed_point_t& p_other) {
      m_value += p_other.m_value;
      return *this;
   }

   constexpr fixed_point_t& operator-=(const fixed_point_t& p_other) {
      m_value -= p_other.m_value;
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

      constexpr rational_t(int64_t p_numerator, uint64_t p_denominator)
         : m_numerator(p_numerator)
         , m_denominator(p_denominator) {}

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
std::ostream& operator<<(std::ostream& p_out, const fixed_point_t<RATIO>& p_fp) {
   if /*constexpr*/ (RATIO::den == 1) {
      return p_out << p_fp.whole_number();
   } else if /*constexpr*/ ((RATIO::den % 10) == 0) {
      // TODO(tybl): Set width of fractional component
      return p_out << p_fp.whole_number() << '.' << p_fp.fraction().m_numerator;
   } else {
      return p_out << p_fp.whole_number() << ' ' << p_fp.fraction().m_numerator << '/' << p_fp.fraction().m_denominator;
   }
}

} // namespace tybl::math

#endif // TYBL_MATH_FIXEDPOINT_HPP

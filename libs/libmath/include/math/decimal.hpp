// License: The Unlicense (https://unlicense.org)
#ifndef TBL_MATH_DECIMAL_HPP
#define TBL_MATH_DECIMAL_HPP

namespace tybl::math {

template <typename mantissa, typename exponent>
struct decimal_t {
   decimal_t();
   bool operator==(const decimal_t &other) const {
      return ((m_value == other.m_value) && (m_factor == other.m_factor));
   }
   bool operator!=(const decimal_t &other) const {
      return !operator==(other);
   }
   bool operator<=(const decimal_t &other) const;
   bool operator>=(const decimal_t &other) const;
   bool operator<(const decimal_t &other) const;
   bool operator>(const decimal_t &other) const;
   decimal_t& operator+=(decimal_t other) {
      const bool fewer = (m_factor < other.m_factor);
      m_value = m_value * (fewer ? other.m_factor / m_factor : 1)
        + other.m_value * (fewer ? 1 : m_factor / other.m_factor);
      m_factor = (fewer ? other.m_factor : m_factor);
      return *this;
   }
   decimal_t& operator-=(decimal_t other) {
      const bool fewer = (m_factor < other.m_factor);
      m_value = m_value * (fewer ? other.m_factor / m_factor : 1)
        - other.m_value * (fewer ? 1 : m_factor / other.m_factor);
      m_factor = (fewer ? other.m_factor : m_factor);
      return *this;
   }
   decimal_t& operator*=(const decimal_t &other) {
      m_value *= other.m_value;
      m_factor *= other.m_factor;
      return *this;
   }
private:
   mantissa m_value;
   exponent m_factor;
};

} // namespace tybl::math

#endif // TBL_MATH_DECIMAL_HPP

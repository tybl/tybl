#pragma once
#ifndef TYBL_MATH_SCALED_HPP
#define TYBL_MATH_SCALED_HPP

namespace tybl::math {

template <typename Type, auto Scale>
struct scaled_numeric {

  explicit scaled_numeric(double p_value) : m_value(static_cast<Type>(p_value * Scale)) {}

  explicit operator double() const { return static_cast<double>(m_value) / Scale; }

  auto rep() const -> Type { return m_value; }

private:
  Type m_value;
}; // struct scaled_numeric

} // namespace tybl::math

#endif // TYBL_MATH_SCALED_HPP
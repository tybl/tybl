#pragma once
#ifndef TYBL_MATH_SCALED_HPP
#define TYBL_MATH_SCALED_HPP

namespace tybl::math {

template <typename Type, Type Scale>
struct scaled_numeric {

  explicit scaled_numeric(Type p_value) : m_value(p_value * Scale) {}

  explicit operator Type() const { return m_value / Scale; }

private:
  Type m_value;
}; // struct scaled_numeric

} // namespace tybl::math

#endif // TYBL_MATH_SCALED_HPP

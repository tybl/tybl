// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LYNEL_MATRIX_HPP
#define TYBL_LYNEL_MATRIX_HPP

#include <array>
#include <cassert> // assert()
#include <cstdlib> // size_t

namespace tybl::lynel {

// Matrix generalization
template <typename Type, size_t Rows, size_t Cols>
struct matrix {
  static_assert(0 < Rows);
  static_assert(0 < Cols);

  using value_type = Type;
  using reference = value_type&;
  using const_reference = value_type const&;
  using size_type = size_t;

  std::array<Type, Rows * Cols> m_array;

  [[nodiscard]] constexpr auto operator()(size_t p_i, size_t p_j) const -> const_reference {
    assert(p_i < Rows);
    assert(p_j < Cols);
    return m_array.at(p_i * Cols + p_j);
  }

  constexpr auto operator()(size_t p_i, size_t p_j) -> reference {
    assert(p_i < Rows);
    assert(p_j < Cols);
    return m_array.at(p_i * Cols + p_j);
  }

  auto operator*=(value_type p_s) -> matrix& {
    for (auto& e : m_array) {
      e *= p_s;
    }
    return *this;
  }

  auto operator==(matrix const& p_o) const {
    bool result = true;
    for (size_t i = 0; i < Rows * Cols; ++i) {
      result &= (m_array.at(i) == p_o.m_array.at(i));
    }
    return result;
  }

}; // class matrix

template <typename Type, size_t Rows, size_t Cols>
auto operator*(Type p_s, matrix<Type, Rows, Cols> const& p_m) -> matrix<Type, Rows, Cols> {
  matrix<Type, Rows, Cols> result;
  for (size_t r = 0; r < Rows; ++r) {
    for (size_t c = 0; c < Cols; ++c) {
      result(r, c) = p_s * p_m(r, c);
    }
  }
  return result;
}

template <typename Type, size_t Rows, size_t Cols>
auto add(matrix<Type, Rows, Cols> const& p_lhs, matrix<Type, Rows, Cols> const& p_rhs) -> matrix<Type, Rows, Cols> {
  matrix<Type, Rows, Cols> result;
  for (size_t r = 0; r < Rows; ++r) {
    for (size_t c = 0; c < Cols; ++c) {
      result(r, c) = p_lhs(r, c) + p_rhs(r, c);
    }
  }
  return result;
}

template <typename Type, size_t Rows, size_t Cols>
auto subtract(matrix<Type, Rows, Cols> const& p_lhs, matrix<Type, Rows, Cols> const& p_rhs)
    -> matrix<Type, Rows, Cols> {
  matrix<Type, Rows, Cols> result;
  for (size_t r = 0; r < Rows; ++r) {
    for (size_t c = 0; c < Cols; ++c) {
      result(r, c) = p_lhs(r, c) - p_rhs(r, c);
    }
  }
  return result;
}

template <typename Type, size_t Rows, size_t Middle, size_t Cols>
auto multiply(matrix<Type, Rows, Middle> const& p_lhs, matrix<Type, Middle, Cols> const& p_rhs)
    -> matrix<Type, Rows, Cols> {
  matrix<Type, Rows, Cols> result;
  for (size_t r = 0; r < Rows; ++r) {
    for (size_t c = 0; c < Cols; ++c) {
      Type e = 0;
      for (size_t i = 0; i < Middle; ++i) {
        e += p_lhs(r, i) * p_rhs(i, c);
      }
      result(r, c) = e;
    }
  }
  return result;
}

template <typename Type, size_t Rows, size_t Cols>
auto transpose(matrix<Type, Rows, Cols> const& p_m) -> matrix<Type, Cols, Rows> {
  matrix<Type, Cols, Rows> result; // NOLINT
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      result(j, i) = p_m(i, j);
    }
  }
  return result;
}

} // namespace tybl::lynel

#endif // TYBL_LYNEL_MATRIX_HPP

// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LINAL_MATRIX_HPP
#define TYBL_LINAL_MATRIX_HPP

#include "linal/basic_matrix.hpp"

#include <assert.h> // assert()

namespace tybl::linal {

// Matrix generalization
template <typename Type, size_t Rows, size_t Cols>
struct matrix {
  static_assert(0 < Rows);
  static_assert(0 < Cols);

  using value_type = Type;
  using reference = value_type&;
  using const_reference = value_type const&;
  using size_type = size_t;

  Type m_array[Rows * Cols];

  [[nodiscard]]
  constexpr auto operator()(size_t i, size_t j) const -> const_reference {
    assert(i < Rows);
    assert(j < Cols);
    return m_array[i * Cols + j];
  }

  constexpr auto operator()(size_t i, size_t j) -> reference {
    assert(i < Rows);
    assert(j < Cols);
    return m_array[i * Cols + j];
  }

  auto operator*=(value_type s) -> matrix& {
    for (auto& e : m_array) { e *= s; }
    return *this;
  }

  auto operator==(matrix const& o) const {
    bool result = true;
    for (size_t i = 0; i < Rows * Cols; ++i) {
      result &= (m_array[i] == o.m_array[i]);
    }
    return result;
  }

}; // class matrix

template <typename Type, size_t Rows, size_t Cols>
auto operator*(Type s, matrix<Type,Rows,Cols> const& m) -> matrix<Type,Rows,Cols>
{
  matrix<Type,Rows,Cols> result;
  for (size_t r = 0; r < Rows; ++r) {
    for (size_t c = 0; c < Cols; ++c) {
      result(r,c) = s * m(r,c);
    }
  }
  return result;
}

template <typename Type, size_t Rows, size_t Cols>
auto add(matrix<Type,Rows,Cols> const& lhs, matrix<Type,Rows,Cols> const& rhs) -> matrix<Type,Rows,Cols>
{
  matrix<Type,Rows,Cols> result;
  for (size_t r = 0; r < Rows; ++r) {
    for (size_t c = 0; c < Cols; ++c) {
      result(r,c) = lhs(r,c) + rhs(r,c);
    }
  }
  return result;
}

template <typename Type, size_t Rows, size_t Cols>
auto subtract(matrix<Type,Rows,Cols> const& lhs, matrix<Type,Rows,Cols> const& rhs) -> matrix<Type,Rows,Cols>
{
  matrix<Type,Rows,Cols> result;
  for (size_t r = 0; r < Rows; ++r) {
    for (size_t c = 0; c < Cols; ++c) {
      result(r,c) = lhs(r,c) - rhs(r,c);
    }
  }
  return result;
}

template <typename Type, size_t Rows, size_t Middle, size_t Cols>
auto multiply(matrix<Type,Rows,Middle> const& lhs, matrix<Type,Middle,Cols> const& rhs) -> matrix<Type,Rows,Cols>
{
  matrix<Type,Rows,Cols> result;
  for (size_t r = 0; r < Rows; ++r) {
    for (size_t c = 0; c < Cols; ++c) {
      Type e = 0;
      for (size_t i = 0; i < Middle; ++i) {
        e += lhs(r,i) * rhs(i,c);
      }
      result(r,c) = e;
    }
  }
  return result;
}

template <typename Type, size_t Rows, size_t Cols>
auto transpose(matrix<Type,Rows,Cols> const& m) -> matrix<Type,Cols,Rows> {
  matrix<Type,Cols,Rows> result;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      result(j,i) = m(i,j);
    }
  }
  return result;
}

} // namespace tybl::linal

#endif // TYBL_LINAL_MATRIX_HPP

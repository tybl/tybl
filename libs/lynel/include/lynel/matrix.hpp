// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LYNEL_MATRIX_HPP
#define TYBL_LYNEL_MATRIX_HPP

#include <assert.h> // assert()
#include <stddef.h> // size_t

namespace tybl::lynel {

template <typename Type, size_t Rows, size_t Cols>
struct matrix {
  static_assert(0 < Rows);
  static_assert(0 < Cols);

  using value_type = Type;
  using reference = value_type&;
  using const_reference = value_type const&;
  using size_type = size_t;

  //Type m_array[Rows][Cols];
  Type m_array[Rows * Cols];

  [[nodiscard]]
  constexpr auto operator()(size_t i, size_t j) const -> const_reference {
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

}; // class matrix

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

} // namespace tybl::lynel

#endif // TYBL_LYNEL_MATRIX_HPP

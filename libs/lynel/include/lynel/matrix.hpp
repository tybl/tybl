// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LYNEL_MATRIX_HPP
#define TYBL_LYNEL_MATRIX_HPP

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

  Type m_array[Rows][Cols];

  [[nodiscard]]
  constexpr auto operator()(size_t i, size_t j) const -> const_reference {
    return m_array[i][j];
  }

  constexpr auto operator()(size_t i, size_t j) -> reference {
    return m_array[i][j];
  }

}; // class matrix

} // namespace tybl::lynel

#endif // TYBL_LYNEL_MATRIX_HPP

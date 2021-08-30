// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LYNEL_MATRIX_HPP
#define TYBL_LYNEL_MATRIX_HPP

#include <array>

namespace tybl::lynel {

template <typename Type, std::size_t Rows, std::size_t Cols>
class matrix {
  std::array<Type, Rows * Cols> m_array;
public:
  using value_type = Type;

  [[nodiscard]]
  constexpr auto operator()(std::size_t i, std::size_t j) const -> value_type const& {
    return m_array[i * j];
  }

  constexpr auto operator()(std::size_t i, std::size_t j) -> value_type& {
    return m_array[i * j];
  }

}; // class matrix

} // namespace tybl::lynel

#endif // TYBL_LYNEL_MATRIX_HPP

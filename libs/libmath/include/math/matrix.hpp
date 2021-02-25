// License: The Unlicense (https://unlicense.org)
#pragma once

#include <array>

namespace tybl::math {

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

} // namespace tybl::math

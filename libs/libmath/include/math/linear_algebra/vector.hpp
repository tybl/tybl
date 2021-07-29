// License: The Unlicense (https://unlicense.org)
#pragma once

#include <array>

namespace tybl::math {

template <typename T, std::size_t N>
class vector {
  std::array<T,N> m_array;
public:
  using value_type = T;

  [[nodiscard]]
  constexpr auto operator()(std::size_t i) const -> value_type const& {
    return m_array[i];
  }

  constexpr auto operator()(std::size_t i) -> value_type& {
    return m_array[i];
  }

}; // class vector

} // namespace tybl::math

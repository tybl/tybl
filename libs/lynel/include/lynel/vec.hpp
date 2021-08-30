// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LYNEL_VEC_HPP
#define TYBL_LYNEL_VEC_HPP

#include <cstddef> // std::size_t, std::ptrdiff_t

namespace tybl::lynel {

template <typename T, std::size_t N>
struct vec {

  // types:
  using value_type = T;
  using reference = value_type&;
  using const_reference = value_type const&;
  using iterator = value_type*;
  using const_iterator = value_type const*;
  using pointer = value_type*;
  using const_pointer = value_type const*;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

private:
  value_type m_data[N];
public:

  // element access:
  [[nodiscard]] constexpr auto operator[](size_type n) noexcept -> reference {
    assert(n < N);
    return m_elems[n];
  }

  [[nodiscard]] constexpr auto operator[](size_type n) const noexcept -> const_reference {
    assert(n < N);
    return m_elems[n];
  }

  [[nodiscard]] constexpr auto operator()(size_type n) -> reference {
    if (n >= N) { throw std::out_of_range("array::at"); }
    return m_elems[n];
  }

  [[nodiscard]] constexpr auto operator()(size_type n) const -> const_reference {
    if (n >= N) { throw std::out_of_range("array::at"); }
    return m_elems[n];
  }

  // operations
  vec& operator+=(vec const& o);
  vec& operator-=(vec const& o);

}; // struct vec<T,N>

template <>
using 

} // namespace tybl::lynel

#endif // TYBL_LYNEL_VEC_HPP

// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LINAL_VECTOR_HPP
#define TYBL_LINAL_VECTOR_HPP

#include <cassert>     // assert
#include <stdexcept>   // std::out_of_range
#include <type_traits> // std::is_nothrow_swappable

namespace tybl::linal {

template <typename T, std::size_t N>
struct vector {
  static_assert(0 < N, "");

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

  value_type m_elems[N];

  // No explicit construct/copy/destroy for aggregate type

  constexpr void fill(const_reference val) {
    for (auto& elem : m_elems) {
      elem = val;
    }
  }

  // iterators:
  [[nodiscard]] constexpr auto begin() noexcept -> iterator { return iterator(data()); }
  [[nodiscard]] constexpr auto begin() const noexcept -> const_iterator { return const_iterator(data()); }
  [[nodiscard]] constexpr auto end() noexcept -> iterator { return iterator(data() + N); }
  [[nodiscard]] constexpr auto end() const noexcept -> const_iterator { return const_iterator(data() + N); }

  // capacity:
  [[nodiscard]] constexpr auto size() const noexcept -> size_type { return N; }
  [[nodiscard]] constexpr auto empty() const noexcept -> bool { return N == 0; }

  // element access:
  [[nodiscard]] constexpr auto operator()(size_type n) noexcept -> reference {
    assert(n < N);
    return m_elems[n];
  }
  [[nodiscard]] constexpr auto operator()(size_type n) const noexcept -> const_reference {
    assert(n < N);
    return m_elems[n];
  }
  [[nodiscard]] constexpr auto at(size_type n) -> reference {
    if (n >= N) {
      throw std::out_of_range("vector::at");
    }
    return m_elems[n];
  }
  [[nodiscard]] constexpr auto at(size_type n) const -> const_reference {
    if (n >= N) {
      throw std::out_of_range("vector::at");
    }
    return m_elems[n];
  }

  [[nodiscard]] constexpr auto data() noexcept -> pointer { return static_cast<pointer>(m_elems); }
  [[nodiscard]] constexpr auto data() const noexcept -> const_pointer { return static_cast<const_pointer>(m_elems); }

  // comparisons:
  auto operator<=>(vector<T, N> const&) const = default;

}; // class vector

} // namespace tybl::linal

#endif // TYBL_LINAL_VECTOR_HPP

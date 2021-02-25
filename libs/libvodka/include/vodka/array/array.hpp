// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_ARRAY_ARRAY_HPP
#define TYBL_VODKA_ARRAY_ARRAY_HPP

#ifndef TYBL_CAN_SYNTHESIZE_COMPARISONS
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=93480
#define TYBL_CAN_SYNTHESIZE_COMPARISONS 0
#endif // TYBL_CAN_SYNTHESIZE_COMPARISONS

#include <algorithm> // std::swap_ranges
#include <cassert>   // assert
#if TYBL_CAN_SYNTHESIZE_COMPARISONS
#include <compare>     // operator<=>
#endif                 // TYBL_CAN_SYNTHESIZE_COMPARISONS
#include <cstddef>     // size_t
#include <stdexcept>   // std::out_of_range
#include <type_traits> // std::is_nothrow_swappable

namespace tybl::vodka {

template <typename T, size_t N>
struct array {
  static_assert(0 < N);

  // types:
  using value_type = T;
  using reference = value_type&;
  using const_reference = value_type const&;
  using iterator = value_type*;
  using const_iterator = value_type const*;
  using pointer = value_type*;
  using const_pointer = value_type const*;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

  value_type m_elems[N];

  // No explicit construct/copy/destroy for aggregate type

  constexpr void fill(const_reference val) {
    for (auto& elem : m_elems) {
      elem = val;
    }
  }

  constexpr void swap(array& a) noexcept(std::is_nothrow_swappable<value_type>::value) { std::swap_ranges(data(), data() + N, a.data()); }

  // iterators:
  [[nodiscard]] constexpr auto begin() noexcept -> iterator { return iterator(data()); }
  [[nodiscard]] constexpr auto begin() const noexcept -> const_iterator { return const_iterator(data()); }
  [[nodiscard]] constexpr auto end() noexcept -> iterator { return iterator(data() + N); }
  [[nodiscard]] constexpr auto end() const noexcept -> const_iterator { return const_iterator(data() + N); }

  // capacity:
  [[nodiscard]] constexpr auto size() const noexcept -> size_type { return N; }
  [[nodiscard]] constexpr auto empty() const noexcept -> bool { return N == 0; }

  // element access:
  [[nodiscard]] constexpr auto operator[](size_type n) noexcept -> reference {
    assert(n < N);
    return m_elems[n];
  }
  [[nodiscard]] constexpr auto operator[](size_type n) const noexcept -> const_reference {
    assert(n < N);
    return m_elems[n];
  }
  [[nodiscard]] constexpr auto at(size_type n) -> reference {
    if (n >= N) {
      throw std::out_of_range("array::at");
    }
    return m_elems[n];
  }
  [[nodiscard]] constexpr auto at(size_type n) const -> const_reference {
    if (n >= N) {
      throw std::out_of_range("array::at");
    }
    return m_elems[n];
  }
  [[nodiscard]] constexpr auto front() noexcept -> reference { return (*this)[0]; }
  [[nodiscard]] constexpr auto front() const noexcept -> const_reference { return (*this)[0]; }
  [[nodiscard]] constexpr auto back() noexcept -> reference { return (*this)[N - 1]; }
  [[nodiscard]] constexpr auto back() const noexcept -> const_reference { return (*this)[N - 1]; }
  [[nodiscard]] constexpr auto data() noexcept -> pointer { return static_cast<pointer>(m_elems); }
  [[nodiscard]] constexpr auto data() const noexcept -> const_pointer { return static_cast<const_pointer>(m_elems); }

#if TYBL_CAN_SYNTHESIZE_COMPARISONS
  // comparisons:
  auto operator<=>(array<T, N> const&) const = default;
#endif

}; // struct array

#if !TYBL_CAN_SYNTHESIZE_COMPARISONS
template <typename T, size_t N>
constexpr auto operator==(array<T, N> const& lhs, array<T, N> const& rhs) -> bool {
  auto l = lhs.begin(), e = lhs.end(), r = rhs.begin();
  do { // array cannot be zero sized, so we can safely dereference begin()
    if (*l != *r) {
      return false;
    }
    ++l;
    ++r;
  } while (l != e);
  return true;
}

template <typename T, size_t N>
constexpr auto operator!=(array<T, N> const& lhs, array<T, N> const& rhs) -> bool {
  return !(lhs == rhs);
}

template <typename T, size_t N>
constexpr auto operator<(array<T, N> const& lhs, array<T, N> const& rhs) -> bool {
  auto l = lhs.begin(), e = lhs.end(), r = rhs.begin();
  do { // array cannot be zero sized, so we can safely dereference begin()
    if (*l < *r) {
      return true;
    }
    ++l;
    ++r;
  } while (l != e);
  return false;
}

template <typename T, size_t N>
constexpr auto operator>(array<T, N> const& lhs, array<T, N> const& rhs) -> bool {
  return rhs < lhs;
}

template <typename T, size_t N>
constexpr auto operator<=(array<T, N> const& lhs, array<T, N> const& rhs) -> bool {
  return !(rhs < lhs);
}

template <typename T, size_t N>
constexpr auto operator>=(array<T, N> const& lhs, array<T, N> const& rhs) -> bool {
  return !(lhs < rhs);
}
#endif // !TYBL_CAN_SYNTHESIZE_COMPARISONS

} // namespace tybl::vodka

#undef TYBL_CAN_SYNTHESIZE_COMPARISONS

#endif // TYBL_VODKA_ARRAY_ARRAY_HPP

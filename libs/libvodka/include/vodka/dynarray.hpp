// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_DYNARRAY_HPP
#define TYBL_VODKA_DYNARRAY_HPP

#include <algorithm>
#include <cstddef>

namespace tybl::vodka {

template <typename ElementType>
struct dynarray final {

  // types:
  using value_type      = ElementType;
  using reference       = value_type&;
  using const_reference = value_type const&;
  using iterator        = value_type*;
  using const_iterator  = value_type const*;
  using pointer         = value_type*;
  using const_pointer   = value_type const*;
  using size_type       = std::size_t;
  using difference_type = std::ptrdiff_t;

private:

  // Points to the dynamically allocated array
  pointer   m_data;

  // 
  size_type m_size{};

public:

  explicit dynarray(size_type p_capacity)
    : m_data(new value_type[p_capacity])
    , m_size(p_capacity)
  {
  }

  dynarray(dynarray const& p_other)
    : m_data(new value_type[p_other.m_size])
    , m_size(p_other.m_size)
  {
    std::copy(p_other.begin(), p_other.end(), std::begin(m_data));
  }

  dynarray(dynarray&& p_other) noexcept
    : m_data(p_other.m_data)
    , m_size(p_other.m_size)
  {
    p_other.m_data = nullptr;
  }

  ~dynarray() { delete [] m_data; }

  auto operator=(dynarray const& p_other) -> dynarray& {
    if (this != &p_other) {
      if (m_size != p_other.m_size) {
        delete [] m_data;
        m_data = p_other.m_size ? new value_type[p_other.m_size] : nullptr;
        m_size = p_other.m_size;
      }
      std::copy(p_other.begin(), p_other.end(), m_data);
    }
    return *this;
  }

  auto operator=(dynarray&& p_other) noexcept -> dynarray& {
    assert(this != &p_other);
    delete [] m_data;
    m_data = p_other.m_data;
    m_size = p_other.m_size;
    p_other.m_data = nullptr;
    p_other.m_size = 0U;
    return *this;
  }

  // Element Access
  auto operator[](size_type p_index) -> reference { return m_data[p_index]; }

  [[nodiscard]] auto operator[](size_type p_index) const -> const_reference { return m_data[p_index]; }

  // Iterators
  [[nodiscard]] auto begin() const -> const_iterator { return m_data; }

  [[nodiscard]] auto end() const -> const_iterator { return m_data + m_size; }

  // Capacity
  [[nodiscard]] auto empty() const -> bool { return 0U == m_size; }

  [[nodiscard]] auto size() const -> size_type { return m_size; }

}; // struct dynarray

} // namespace tybl::vodka

#endif // TYBL_VODKA_DYNARRAY_HPP

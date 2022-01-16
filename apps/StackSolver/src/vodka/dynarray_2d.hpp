// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_DYNARRAY2D_HPP
#define TYBL_VODKA_DYNARRAY2D_HPP

#include <cstring> // memcpy
#include <memory> // std::unique_ptr
#include <span>

namespace tybl::vodka {

template <typename T>
struct dynarray_2d {

  // types:
  using value_type = T;
  using reference = value_type&;
  using const_reference = value_type const&;
  using pointer = value_type*;
  using const_pointer = value_type const*;
  using size_type = size_t;

private:
  std::unique_ptr<value_type[]> m_data;
  size_type m_rows;
  size_type m_cols;
public:
  dynarray_2d(size_t p_r, size_t p_c)
    : m_data((0 < p_c && 0 < p_r) ? (std::make_unique<value_type[]>(p_c*p_r)) : nullptr)
    , m_rows(p_r)
    , m_cols(p_c)
  {
  }

  dynarray_2d(dynarray_2d&& p_o)
    : m_data(std::move(p_o.m_data))
    , m_rows(p_o.m_rows)
    , m_cols(p_o.m_cols)
  {
  }

  dynarray_2d(dynarray_2d const& p_o)
    : m_data(p_o.m_data ? std::make_unique<value_type[]>(p_o.m_cols*p_o.m_rows) : nullptr)
    , m_rows(p_o.m_rows)
    , m_cols(p_o.m_cols)
  {
    memcpy(m_data.get(), p_o.m_data.get(), m_cols*m_rows);
  }

  ~dynarray_2d() = default;

  const_reference operator()(size_t p_r, size_t p_c) const {
    return m_data[m_cols*p_r + p_c];
  }

  reference operator()(size_t p_r, size_t p_c) {
    return m_data[m_cols*p_r + p_c];
  }

  bool operator<(dynarray_2d const& p_o) const {
    const_pointer first1_p = m_data.get();
    const_pointer first2_p = p_o.m_data.get();
    const_pointer last1_p = first1_p + m_cols * m_rows;
    const_pointer last2_p = first2_p + p_o.m_cols * p_o.m_rows;
    for (;(first1_p != last1_p) && (first2_p != last2_p); ++first1_p, ++first2_p) {
      if (*first1_p < *first2_p) return true;
      if (*first2_p < *first1_p) return false;
    }
    return (first1_p == last1_p) && (first2_p != last2_p);
  }

  size_type cols() const { return m_cols; }

  size_type rows() const { return m_rows; }

  std::span<const value_type> row(size_t p_r) const {
    return std::span<const value_type>(m_data.get() + (m_cols * p_r), m_cols);
  }

}; // struct dynarray_2d

} // namespace tybl::vodka

#endif // TYBL_VODKA_DYNARRAY2D_HPP

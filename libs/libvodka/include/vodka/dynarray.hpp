// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef _TYBL__VODKA__DYNARRAY__HPP_
#define _TYBL__VODKA__DYNARRAY__HPP_

namespace tybl::vodka {

template <typename ElementType>
struct dynarray {

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
  size_type m_capacity;
  size_type m_size;

public:

  dynarray(size_type p_capacity)
    : m_data(new value_type[p_capacity])
    , m_capacity(p_capacity)
  {
  }

  ~dynarray()
  {
    delete [] m_data;
  }

  dynarray& operator=(dynarray p_other)
  {
  }

  reference operator[](size_type p_index) {
    return m_data[p_index];
  }

  const_reference operator[](size_type p_index) const {
    return m_data[p_index];
  }

  bool empty() const {
    return !m_size;
  }

  size_type size() const {
    return m_size;
  }

  size_type capacity() const {
    return m_capacity;
  }

}; // struct dynarray

}; // namespace tybl::vodka

#endif // _TYBL__VODKA__DYNARRAY__HPP_

// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef _TYBL__VODKA__STRING_VIEW__BASIC_STRING_VIEW__HPP_
#define _TYBL__VODKA__STRING_VIEW__BASIC_STRING_VIEW__HPP_

#include "vodka/algorithm/min.hpp"
#include "vodka/type_traits/is_same.hpp"

#include <cassert>   // assert()
#include <iosfwd>    // std::ostream
#include <limits>    // std::numeric_limits
#include <stdexcept> // std::out_of_range
#include <string>    // std::char_traits

// Included by unknown:
// std::numeric_limits
// std::is_array_v
// std::is_standard_layout_v
// std::is_trivial_v
// std::common_type_t

namespace tybl::vodka {

// str_find_first_not_of
template<class CharType, class _SizeT, class CharTraits, _SizeT __npos>
_SizeT constexpr str_find_first_not_of(const CharType * p_p, _SizeT p_sz, const CharType* p_s, _SizeT p_pos, _SizeT p_n) noexcept {
  if (p_pos < p_sz) {
    const CharType* pe_p = p_p + p_sz;
    for (const CharType* ps_p = p_p + p_pos; ps_p != pe_p; ++ps_p) {
      if (CharTraits::find(p_s, p_n, *ps_p) == nullptr) {
        return static_cast<_SizeT>(ps_p - p_p);
      }
    }
  }
  return __npos;
}


template<class CharType, class _SizeT, class CharTraits, _SizeT __npos>
_SizeT constexpr str_find_first_not_of(const CharType * p_p, _SizeT p_sz, CharType p_c, _SizeT p_pos)  noexcept {
  if (p_pos < p_sz) {
    const CharType* pe_p = p_p + p_sz;
    for (const CharType* ps_p = p_p + p_pos; ps_p != pe_p; ++ps_p) {
      if (!CharTraits::eq(*ps_p, p_c)) {
        return static_cast<_SizeT>(ps_p - p_p);
      }
    }
  }
  return __npos;
}

template <class CharType, class CharTraits = std::char_traits<CharType>>
struct basic_string_view {

  // types
  using traits_type = CharTraits;
  using value_type = CharType;
  using pointer = value_type*;
  using const_pointer = value_type const*;
  using reference = value_type&;
  using const_reference = value_type const&;
  using iterator = const_pointer;
  using const_iterator = const_pointer;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

  static constexpr const size_type npos = std::numeric_limits<size_type>::max();

  static_assert(!std::is_array_v<value_type>, "Character type of basic_string_view must not be an array");
  static_assert(std::is_standard_layout_v<value_type>, "Character type of basic_string_view must be standard-layout");
  static_assert(std::is_trivial_v<value_type>, "Character type of basic_string_view must be trivial");
  static_assert(is_same_v<CharType, typename traits_type::char_type>, "traits_type::char_type must be the same type as CharT");

private:
  const_pointer m_data;
  size_type m_size;

public:
  // [string.view.cons], construct/copy
  constexpr basic_string_view() noexcept
    : m_data(nullptr)
    , m_size(0) {}

  constexpr basic_string_view(basic_string_view const&) noexcept = default;

  constexpr basic_string_view& operator=(basic_string_view const&) noexcept = default;

  constexpr basic_string_view(CharType const* p_s, size_type p_len) noexcept
    : m_data(p_s)
    , m_size(p_len) {
    assert(p_len == 0 || p_s != nullptr);
  }

  explicit constexpr basic_string_view(CharType const* p_s)
    : m_data(p_s)
    , m_size(traits_type::length(p_s)) {}

  // [string.view.iterators], iterators
  [[nodiscard]] constexpr auto begin() const noexcept -> const_iterator { return cbegin(); }
  [[nodiscard]] constexpr auto end() const noexcept -> const_iterator { return cend(); }
  [[nodiscard]] constexpr auto cbegin() const noexcept -> const_iterator { return m_data; }
  [[nodiscard]] constexpr auto cend() const noexcept -> const_iterator { return m_data + m_size; }

#if 0
  [[nodiscard]] inline
  const_reverse_iterator rbegin()   const noexcept { return const_reverse_iterator(cend()); }

  [[nodiscard]] inline
  const_reverse_iterator rend()     const noexcept { return const_reverse_iterator(cbegin()); }

  [[nodiscard]] inline
  const_reverse_iterator crbegin()  const noexcept { return const_reverse_iterator(cend()); }

  [[nodiscard]] inline
  const_reverse_iterator crend()    const noexcept { return const_reverse_iterator(cbegin()); }
#endif

  // [string.view.capacity], capacity
  [[nodiscard]] constexpr size_type size() const noexcept { return m_size; }

  [[nodiscard]] constexpr size_type length() const noexcept { return m_size; }

  [[nodiscard]] constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max() / sizeof(value_type); }

  [[nodiscard]] constexpr bool empty() const noexcept { return m_size == 0; }

  // [string.view.access], element access
  [[nodiscard]] constexpr auto operator[](size_type p_pos) const noexcept -> const_reference {
    return m_data[p_pos];
  }

  [[nodiscard]] constexpr auto at(size_type p_pos) const -> const_reference {
    return (p_pos >= size()) ? (throw std::out_of_range("string_view::at"), m_data[0]) : m_data[p_pos];
  }

  [[nodiscard]] constexpr auto front() const noexcept -> const_reference {
    return m_data[0];
  }

  [[nodiscard]] constexpr auto back() const noexcept -> const_reference {
    return /*_LIBCPP_ASSERT(!empty(), "string_view::back(): string is empty"),*/ m_data[m_size - 1];
  }

  constexpr const_pointer data() const noexcept { return m_data; }

  // [string.view.modifiers], modifiers:
  constexpr void remove_prefix(size_type p_n) noexcept {
    m_data += p_n;
    m_size -= p_n;
  }

  constexpr void remove_suffix(size_type p_n) noexcept {
    m_size -= p_n;
  }

  constexpr void swap(basic_string_view& p_o) noexcept {
    const value_type* __p = m_data;
    m_data = p_o.m_data;
    p_o.m_data = __p;

    size_type __sz = m_size;
    m_size = p_o.m_size;
    p_o.m_size = __sz;
  }

  inline size_type copy(CharType* p_str, size_type p_n, size_type p_pos = 0) const {
    if (p_pos > size()) {
      throw std::out_of_range("string_view::copy");
    }
    size_type __rlen = min(p_n, size() - p_pos);
    CharTraits::copy(p_str, data() + p_pos, __rlen);
    return __rlen;
  }

  constexpr basic_string_view substr(size_type p_pos = 0, size_type p_n = npos) const {
    return p_pos > size() ? (throw std::out_of_range("string_view::substr"), basic_string_view())
                          : basic_string_view(data() + p_pos, min(p_n, size() - p_pos));
  }

  constexpr int compare(basic_string_view p_sv) const noexcept {
    size_type min_len = ::tybl::vodka::min(size(), p_sv.size());
    int result = CharTraits::compare(data(), p_sv.data(), min_len);
    if (result == 0 && size() != p_sv.size()) { // first min_len chars matched
      result = size() < p_sv.size() ? -1 : 1;
    }
    return result;
  }

  constexpr int compare(size_type p_pos, size_type p_n, basic_string_view p_sv) const {
    return substr(p_pos, p_n).compare(p_sv);
  }

  constexpr int compare(size_type p_pos1, size_type p_n1, basic_string_view p_sv, size_type p_pos2,
                               size_type p_n2) const {
    return substr(p_pos1, p_n1).compare(p_sv.substr(p_pos2, p_n2));
  }

  constexpr int compare(const CharType* p_str) const noexcept { return compare(basic_string_view(p_str)); }

  constexpr int compare(size_type p_pos, size_type p_n, const CharType* p_str) const {
    return substr(p_pos, p_n).compare(basic_string_view(p_str));
  }

  constexpr int compare(size_type p_pos, size_type p_n1, const CharType* p_str, size_type p_n2) const {
    return substr(p_pos, p_n1).compare(basic_string_view(p_str, p_n2));
  }

#if 0
  // find
  constexpr inline
  size_type find(basic_string_view str, size_type __pos = 0) const noexcept {
    _LIBCPP_ASSERT(str.size() == 0 || str.data() != nullptr, "string_view::find(): received nullptr");
    return __str_find<value_type, size_type, traits_type, npos>(data(), size(), str.data(), __pos, str.size());
  }

  constexpr inline
  size_type find(CharType __c, size_type __pos = 0) const noexcept {
      return __str_find<value_type, size_type, traits_type, npos>
          (data(), size(), __c, __pos);
  }

  constexpr inline
  size_type find(const CharType* str, size_type __pos, size_type __n) const {
      _LIBCPP_ASSERT(__n == 0 || str != nullptr, "string_view::find(): received nullptr");
      return __str_find<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, __n);
  }

  constexpr inline
  size_type find(const CharType* str, size_type __pos = 0) const {
      _LIBCPP_ASSERT(str != nullptr, "string_view::find(): received nullptr");
      return __str_find<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, traits_type::length(str));
  }

  // rfind
  constexpr inline
  size_type rfind(basic_string_view str, size_type __pos = npos) const noexcept {
      _LIBCPP_ASSERT(str.size() == 0 || str.data() != nullptr, "string_view::find(): received nullptr");
      return __str_rfind<value_type, size_type, traits_type, npos>
          (data(), size(), str.data(), __pos, str.size());
  }

  constexpr inline
  size_type rfind(CharType __c, size_type __pos = npos) const noexcept {
      return __str_rfind<value_type, size_type, traits_type, npos>
          (data(), size(), __c, __pos);
  }

  constexpr inline
  size_type rfind(const CharType* str, size_type __pos, size_type __n) const {
      _LIBCPP_ASSERT(__n == 0 || str != nullptr, "string_view::rfind(): received nullptr");
      return __str_rfind<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, __n);
  }

  constexpr inline
  size_type rfind(const CharType* str, size_type __pos=npos) const {
      _LIBCPP_ASSERT(str != nullptr, "string_view::rfind(): received nullptr");
      return __str_rfind<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, traits_type::length(str));
  }

  // find_first_of
  constexpr inline
  size_type find_first_of(basic_string_view str, size_type __pos = 0) const noexcept {
      _LIBCPP_ASSERT(str.size() == 0 || str.data() != nullptr, "string_view::find_first_of(): received nullptr");
      return __str_find_first_of<value_type, size_type, traits_type, npos>
          (data(), size(), str.data(), __pos, str.size());
  }

  constexpr inline
  size_type find_first_of(CharType __c, size_type __pos = 0) const noexcept
  { return find(__c, __pos); }

  constexpr inline
  size_type find_first_of(const CharType* str, size_type __pos, size_type __n) const
  {
      _LIBCPP_ASSERT(__n == 0 || str != nullptr, "string_view::find_first_of(): received nullptr");
      return __str_find_first_of<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, __n);
  }

  constexpr inline
  size_type find_first_of(const CharType* str, size_type __pos=0) const
  {
      _LIBCPP_ASSERT(str != nullptr, "string_view::find_first_of(): received nullptr");
      return __str_find_first_of<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, traits_type::length(str));
  }

  // find_last_of
  constexpr inline
  size_type find_last_of(basic_string_view str, size_type __pos=npos) const noexcept
  {
      _LIBCPP_ASSERT(str.size() == 0 || str.data() != nullptr, "string_view::find_last_of(): received nullptr");
      return __str_find_last_of<value_type, size_type, traits_type, npos>
          (data(), size(), str.data(), __pos, str.size());
  }

  constexpr inline
  size_type find_last_of(CharType __c, size_type __pos = npos) const noexcept
  { return rfind(__c, __pos); }

  constexpr inline
  size_type find_last_of(const CharType* str, size_type __pos, size_type __n) const
  {
      _LIBCPP_ASSERT(__n == 0 || str != nullptr, "string_view::find_last_of(): received nullptr");
      return __str_find_last_of<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, __n);
  }

  constexpr inline
  size_type find_last_of(const CharType* str, size_type __pos=npos) const
  {
      _LIBCPP_ASSERT(str != nullptr, "string_view::find_last_of(): received nullptr");
      return __str_find_last_of<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, traits_type::length(str));
  }


#endif


  // find_first_not_of
  constexpr auto find_first_not_of(basic_string_view p_str, size_type p_pos =0) const noexcept -> size_type
  {
      return str_find_first_not_of<value_type, size_type, traits_type, npos>(data(), size(), p_str.data(), p_pos,
                                                                           p_str.size());
  }

  constexpr auto find_first_not_of(CharType p_c, size_type p_pos =0) const noexcept -> size_type
  {
      return str_find_first_not_of<value_type, size_type, traits_type, npos>(data(), size(), p_c, p_pos);
  }

  constexpr auto find_first_not_of(const CharType* p_str, size_type p_pos, size_type p_n) const -> size_type
  {
      return str_find_first_not_of<value_type, size_type, traits_type, npos>(data(), size(), p_str, p_pos, p_n);
  }

  constexpr auto find_first_not_of(const CharType* p_string, size_type p_position = 0) const -> size_type
  {
      return str_find_first_not_of<value_type, size_type, traits_type, npos>(data(), size(), p_string, p_position,
                                                                           traits_type::length(p_string));
  }

#if 0
  // find_last_not_of
  constexpr inline
  size_type find_last_not_of(basic_string_view str, size_type __pos=npos) const noexcept
  {
      _LIBCPP_ASSERT(str.size() == 0 || str.data() != nullptr, "string_view::find_last_not_of(): received nullptr");
      return __str_find_last_not_of<value_type, size_type, traits_type, npos>
          (data(), size(), str.data(), __pos, str.size());
  }

  constexpr inline
  size_type find_last_not_of(CharType __c, size_type __pos=npos) const noexcept
  {
      return __str_find_last_not_of<value_type, size_type, traits_type, npos>
          (data(), size(), __c, __pos);
  }

  constexpr inline
  size_type find_last_not_of(const CharType* str, size_type __pos, size_type __n) const
  {
      _LIBCPP_ASSERT(__n == 0 || str != nullptr, "string_view::find_last_not_of(): received nullptr");
      return __str_find_last_not_of<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, __n);
  }

  constexpr inline
  size_type find_last_not_of(const CharType* __s, size_type __pos=npos) const
  {
      _LIBCPP_ASSERT(__s != nullptr, "string_view::find_last_not_of(): received nullptr");
      return __str_find_last_not_of<value_type, size_type, traits_type, npos>
          (data(), size(), __s, __pos, traits_type::length(__s));
  }

  constexpr inline
  bool starts_with(basic_string_view __s) const noexcept
  { return size() >= __s.size() && compare(0, __s.size(), __s) == 0; }

  constexpr inline
  bool starts_with(value_type __c) const noexcept
  { return !empty() && CharTraits::eq(front(), __c); }

  constexpr inline
  bool starts_with(const value_type* __s) const noexcept
  { return starts_with(basic_string_view(__s)); }

  constexpr inline
  bool ends_with(basic_string_view __s) const noexcept
  { return size() >= __s.size() && compare(size() - __s.size(), npos, __s) == 0; }

  constexpr inline
  bool ends_with(value_type __c) const noexcept
  { return !empty() && CharTraits::eq(back(), __c); }

  constexpr inline
  bool ends_with(const value_type* __s) const noexcept
  { return ends_with(basic_string_view(__s)); }
#endif

}; // class basic_string_view

// [string.view.comparison]
// operator ==
template <class CharType, class CharTraits>
constexpr auto operator==(basic_string_view<CharType, CharTraits> p_lhs,
                          basic_string_view<CharType, CharTraits> p_rhs) noexcept -> bool {
  if (p_lhs.size() != p_rhs.size()) {
    return false;
  }
  return p_lhs.compare(p_rhs) == 0;
}

template <class CharType, class CharTraits>
constexpr auto operator==(basic_string_view<CharType, CharTraits> p_lhs,
                          std::common_type_t<basic_string_view<CharType, CharTraits>> p_rhs) noexcept -> bool {
  if (p_lhs.size() != p_rhs.size()) {
    return false;
  }
  return p_lhs.compare(p_rhs) == 0;
}

template <class CharType, class CharTraits>
constexpr auto operator==(std::common_type_t<basic_string_view<CharType, CharTraits>> p_lhs,
                          basic_string_view<CharType, CharTraits> p_rhs) noexcept -> bool {
  if (p_lhs.size() != p_rhs.size()) {
    return false;
  }
  return p_lhs.compare(p_rhs) == 0;
}

// operator !=
template <class CharType, class CharTraits>
constexpr auto operator!=(basic_string_view<CharType, CharTraits> p_lhs,
                          basic_string_view<CharType, CharTraits> p_rhs) noexcept -> bool {
  if (p_lhs.size() != p_rhs.size()) {
    return true;
  }
  return p_lhs.compare(p_rhs) != 0;
}

template <class CharType, class CharTraits>
constexpr auto operator!=(basic_string_view<CharType, CharTraits> p_lhs,
                          std::common_type_t<basic_string_view<CharType, CharTraits>> p_rhs) noexcept -> bool {
  if (p_lhs.size() != p_rhs.size()) {
    return true;
  }
  return p_lhs.compare(p_rhs) != 0;
}

template <class CharType, class CharTraits>
constexpr auto operator!=(std::common_type_t<basic_string_view<CharType, CharTraits>> p_lhs,
                          basic_string_view<CharType, CharTraits> p_rhs) noexcept -> bool {
  if (p_lhs.size() != p_rhs.size()) {
    return true;
  }
  return p_lhs.compare(p_rhs) != 0;
}

// operator <
template <class CharType, class CharTraits>
constexpr auto operator<(basic_string_view<CharType, CharTraits> p_lhs,
                         basic_string_view<CharType, CharTraits> p_rhs) noexcept -> bool {
  return p_lhs.compare(p_rhs) < 0;
}

template <class CharType, class CharTraits>
constexpr auto operator<(basic_string_view<CharType, CharTraits> p_lhs,
                         std::common_type_t<basic_string_view<CharType, CharTraits>> p_rhs) noexcept -> bool {
  return p_lhs.compare(p_rhs) < 0;
}

template <class CharType, class CharTraits>
constexpr auto operator<(std::common_type_t<basic_string_view<CharType, CharTraits>> p_lhs,
                         basic_string_view<CharType, CharTraits> p_rhs) noexcept -> bool {
  return p_lhs.compare(p_rhs) < 0;
}

// operator >
template <class CharType, class CharTraits>
constexpr auto operator>(basic_string_view<CharType, CharTraits> p_lhs,
                         basic_string_view<CharType, CharTraits> p_rhs) noexcept -> bool {
  return p_lhs.compare(p_rhs) > 0;
}

template <class CharType, class CharTraits>
constexpr auto operator>(basic_string_view<CharType, CharTraits> p_lhs,
                         std::common_type_t<basic_string_view<CharType, CharTraits>> p_rhs) noexcept -> bool {
  return p_lhs.compare(p_rhs) > 0;
}

template <class CharType, class CharTraits>
constexpr auto operator>(std::common_type_t<basic_string_view<CharType, CharTraits>> p_lhs,
                         basic_string_view<CharType, CharTraits> p_rhs) noexcept -> bool {
  return p_lhs.compare(p_rhs) > 0;
}

// operator <=
template <class CharType, class CharTraits>
constexpr auto operator<=(basic_string_view<CharType, CharTraits> p_lhs,
                          basic_string_view<CharType, CharTraits> p_rhs) noexcept -> bool {
  return p_lhs.compare(p_rhs) <= 0;
}

template <class CharType, class CharTraits>
constexpr auto operator<=(basic_string_view<CharType, CharTraits> p_lhs,
                          std::common_type_t<basic_string_view<CharType, CharTraits>> p_rhs) noexcept -> bool {
  return p_lhs.compare(p_rhs) <= 0;
}

template <class CharType, class CharTraits>
constexpr auto operator<=(std::common_type_t<basic_string_view<CharType, CharTraits>> p_lhs,
                          basic_string_view<CharType, CharTraits> p_rhs) noexcept -> bool {
  return p_lhs.compare(p_rhs) <= 0;
}

// operator >=
template <class CharType, class CharTraits>
constexpr auto operator>=(basic_string_view<CharType, CharTraits> p_lhs,
                          basic_string_view<CharType, CharTraits> p_rhs) noexcept -> bool {
  return p_lhs.compare(p_rhs) >= 0;
}

template <class CharType, class CharTraits>
constexpr auto operator>=(basic_string_view<CharType, CharTraits> p_lhs,
                          std::common_type_t<basic_string_view<CharType, CharTraits>> p_rhs) noexcept -> bool {
  return p_lhs.compare(p_rhs) >= 0;
}

template <class CharType, class CharTraits>
constexpr auto operator>=(std::common_type_t<basic_string_view<CharType, CharTraits>> p_lhs,
                          basic_string_view<CharType, CharTraits> p_rhs) noexcept -> bool {
  return p_lhs.compare(p_rhs) >= 0;
}

template<class CharType, class CharTraits>
auto operator<<(std::basic_ostream<CharType, CharTraits>& p_out_stream, basic_string_view<CharType, CharTraits> p_string) -> std::basic_ostream<CharType, CharTraits>& {
  return p_out_stream.write(p_string.data(), static_cast<std::streamsize>(p_string.size()));
}

using string_view = basic_string_view<char>;
using u8string_view = basic_string_view<char8_t>;
using u16string_view = basic_string_view<char16_t>;
using u32string_view = basic_string_view<char32_t>;
using wstring_view = basic_string_view<wchar_t>;

#if 0
// [string.view.hash]
template<class CharType>
struct hash<basic_string_view<CharType, std::char_traits<CharType>>>
    : public unary_function<basic_string_view<CharType, std::char_traits<CharType> >, size_t>
{
    inline
    size_t operator()(const basic_string_view<CharType, std::char_traits<CharType> > __val) const noexcept {
        return __do_string_hash(__val.data(), __val.data() + __val.size());
    }
};
#endif

inline namespace literals {

inline namespace string_view_literals {

constexpr auto operator"" _sv(const char* p_str, size_t p_len) noexcept -> basic_string_view<char> {
  return { p_str, p_len };
  //return basic_string_view<char>(p_str, p_len);
}

constexpr auto operator"" _sv(const wchar_t* p_str, size_t p_len) noexcept -> basic_string_view<wchar_t> {
  return { p_str, p_len };
  //return basic_string_view<wchar_t>(p_str, p_len);
}

constexpr auto operator"" _sv(const char8_t* p_str, size_t p_len) noexcept -> basic_string_view<char8_t> {
  return { p_str, p_len };
  //return basic_string_view<char8_t>(p_str, p_len);
}

constexpr auto operator"" _sv(const char16_t* p_str, size_t p_len) noexcept -> basic_string_view<char16_t> {
  return { p_str, p_len };
  //return basic_string_view<char16_t>(p_str, p_len);
}

constexpr auto operator"" _sv(const char32_t* p_str, size_t p_len) noexcept -> basic_string_view<char32_t> {
  return { p_str, p_len };
  //return basic_string_view<char32_t>(p_str, p_len);
}

} // namespace string_view_literals

} // namespace literals

} // namespace tybl::vodka

#endif // _TYBL__VODKA__STRING_VIEW__BASIC_STRING_VIEW__HPP_

// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_STRINGVIEW_BASICSTRINGVIEW_HPP
#define TYBL_VODKA_STRINGVIEW_BASICSTRINGVIEW_HPP

#include "vodka/algorithm/min.hpp"
#include "vodka/type_traits/is_same.hpp"

#include <cassert>   // assert()
#include <iosfwd>    // std::ostream
#include <stdexcept> // std::out_of_range
#include <string>    // std::char_traits

// Included by unknown:
// std::numeric_limits
// std::is_array_v
// std::is_standard_layout_v
// std::is_trivial_v
// std::common_type_t

namespace tybl::vodka {

template<class _CharT, class _Traits = std::char_traits<_CharT>>
struct basic_string_view {

  // types
  using traits_type = _Traits;
  using value_type = _CharT;
  using pointer = value_type*;
  using const_pointer = value_type const*;
  using reference = value_type&;
  using const_reference = value_type const&;
  using iterator = const_pointer;
  using const_iterator = const_pointer;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

  static constexpr const size_type npos = std::numeric_limits<size_type>::max();

  static_assert((!std::is_array_v<value_type>), "Character type of basic_string_view must not be an array");
  static_assert(( std::is_standard_layout_v<value_type>), "Character type of basic_string_view must be standard-layout");
  static_assert(( std::is_trivial_v<value_type>), "Character type of basic_string_view must be trivial");
  static_assert((is_same_v<_CharT, typename traits_type::char_type>), "traits_type::char_type must be the same type as CharT");

private:
  const_pointer m_data;
  size_type     m_size;
public:

  // [string.view.cons], construct/copy
  constexpr inline
  basic_string_view() noexcept
    : m_data(nullptr)
    , m_size(0) { }

  constexpr inline
  basic_string_view(basic_string_view const&) noexcept = default;

  constexpr inline
  basic_string_view& operator=(basic_string_view const&) noexcept = default;

  constexpr inline
  basic_string_view(_CharT const* s, size_type __len) noexcept
    : m_data(s)
    , m_size(__len)
  {
    assert(__len == 0 || s != nullptr);
  }

  constexpr inline
  basic_string_view(_CharT const* s)
    : m_data(s)
    , m_size(traits_type::length(s)) { }

  // [string.view.iterators], iterators
  [[nodiscard]] constexpr inline auto begin()  const noexcept -> const_iterator { return cbegin(); }
  [[nodiscard]] constexpr inline auto end()    const noexcept -> const_iterator { return cend(); }
  [[nodiscard]] constexpr inline auto cbegin() const noexcept -> const_iterator { return m_data; }
  [[nodiscard]] constexpr inline auto cend()   const noexcept -> const_iterator { return m_data + m_size; }

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
  [[nodiscard]] constexpr inline
  size_type size()     const noexcept { return m_size; }

  [[nodiscard]] constexpr inline
  size_type length()   const noexcept { return m_size; }

  [[nodiscard]] constexpr inline
  size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

  [[nodiscard]] constexpr inline
  bool empty()         const noexcept { return m_size == 0; }

  // [string.view.access], element access
  [[nodiscard]] constexpr inline auto
  operator[](size_type __pos) const noexcept -> const_reference {
    return /*_LIBCPP_ASSERT(__pos < size(), "string_view[] index out of bounds"),*/ m_data[__pos];
  }

  [[nodiscard]] constexpr inline auto
  at(size_type __pos) const -> const_reference {
    return (__pos >= size())
      ? (throw std::out_of_range("string_view::at"), m_data[0])
      : m_data[__pos];
  }

  [[nodiscard]] constexpr inline auto
  front() const noexcept -> const_reference {
    return /*_LIBCPP_ASSERT(!empty(), "string_view::front(): string is empty"),*/ m_data[0];
  }

  [[nodiscard]] constexpr inline auto
  back() const noexcept -> const_reference {
    return /*_LIBCPP_ASSERT(!empty(), "string_view::back(): string is empty"),*/ m_data[m_size-1];
  }

  constexpr inline
  const_pointer data() const noexcept { return m_data; }

  // [string.view.modifiers], modifiers:
  constexpr inline
  void remove_prefix(size_type __n) noexcept {
    /*_LIBCPP_ASSERT(__n <= size(), "remove_prefix() can't remove more than size()");*/
    m_data += __n;
    m_size -= __n;
  }

  constexpr inline
  void remove_suffix(size_type __n) noexcept {
    /*_LIBCPP_ASSERT(__n <= size(), "remove_suffix() can't remove more than size()");*/
    m_size -= __n;
  }

  constexpr inline
  void swap(basic_string_view& o) noexcept {
    const value_type *__p = m_data;
    m_data = o.m_data;
    o.m_data = __p;

    size_type __sz = m_size;
    m_size = o.m_size;
    o.m_size = __sz;
  }

  inline
  size_type copy(_CharT* str, size_type __n, size_type __pos = 0) const {
    if (__pos > size()) throw std::out_of_range("string_view::copy");
    size_type __rlen = min(__n, size() - __pos);
    _Traits::copy(str, data() + __pos, __rlen);
    return __rlen;
  }

  constexpr inline
  basic_string_view substr(size_type __pos = 0, size_type __n = npos) const {
    return __pos > size()
      ? (throw std::out_of_range("string_view::substr"), basic_string_view())
      : basic_string_view(data() + __pos, min(__n, size() - __pos));
  }

  constexpr int compare(basic_string_view __sv) const noexcept {
    size_type __rlen = min( size(), __sv.size());
    int __retval = _Traits::compare(data(), __sv.data(), __rlen);
    if ( __retval == 0 ) // first __rlen chars matched
      __retval = size() == __sv.size() ? 0 : ( size() < __sv.size() ? -1 : 1 );
    return __retval;
  }

  constexpr inline
  int compare(size_type __pos1, size_type __n1, basic_string_view __sv) const {
    return substr(__pos1, __n1).compare(__sv);
  }

  constexpr inline
  int compare(                       size_type __pos1, size_type __n1,
              basic_string_view __sv, size_type __pos2, size_type __n2) const
  {
    return substr(__pos1, __n1).compare(__sv.substr(__pos2, __n2));
  }

  constexpr inline
  int compare(const _CharT* str) const noexcept {
    return compare(basic_string_view(str));
  }

  constexpr inline
  int compare(size_type __pos1, size_type __n1, const _CharT* str) const {
    return substr(__pos1, __n1).compare(basic_string_view(str));
  }

  constexpr inline
  int compare(size_type __pos1, size_type __n1, const _CharT* str, size_type __n2) const {
    return substr(__pos1, __n1).compare(basic_string_view(str, __n2));
  }

#if 0
  // find
  constexpr inline
  size_type find(basic_string_view str, size_type __pos = 0) const noexcept {
    _LIBCPP_ASSERT(str.size() == 0 || str.data() != nullptr, "string_view::find(): received nullptr");
    return __str_find<value_type, size_type, traits_type, npos>(data(), size(), str.data(), __pos, str.size());
  }

  constexpr inline
  size_type find(_CharT __c, size_type __pos = 0) const noexcept {
      return __str_find<value_type, size_type, traits_type, npos>
          (data(), size(), __c, __pos);
  }

  constexpr inline
  size_type find(const _CharT* str, size_type __pos, size_type __n) const {
      _LIBCPP_ASSERT(__n == 0 || str != nullptr, "string_view::find(): received nullptr");
      return __str_find<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, __n);
  }

  constexpr inline
  size_type find(const _CharT* str, size_type __pos = 0) const {
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
  size_type rfind(_CharT __c, size_type __pos = npos) const noexcept {
      return __str_rfind<value_type, size_type, traits_type, npos>
          (data(), size(), __c, __pos);
  }

  constexpr inline
  size_type rfind(const _CharT* str, size_type __pos, size_type __n) const {
      _LIBCPP_ASSERT(__n == 0 || str != nullptr, "string_view::rfind(): received nullptr");
      return __str_rfind<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, __n);
  }

  constexpr inline
  size_type rfind(const _CharT* str, size_type __pos=npos) const {
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
  size_type find_first_of(_CharT __c, size_type __pos = 0) const noexcept
  { return find(__c, __pos); }

  constexpr inline
  size_type find_first_of(const _CharT* str, size_type __pos, size_type __n) const
  {
      _LIBCPP_ASSERT(__n == 0 || str != nullptr, "string_view::find_first_of(): received nullptr");
      return __str_find_first_of<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, __n);
  }

  constexpr inline
  size_type find_first_of(const _CharT* str, size_type __pos=0) const
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
  size_type find_last_of(_CharT __c, size_type __pos = npos) const noexcept
  { return rfind(__c, __pos); }

  constexpr inline
  size_type find_last_of(const _CharT* str, size_type __pos, size_type __n) const
  {
      _LIBCPP_ASSERT(__n == 0 || str != nullptr, "string_view::find_last_of(): received nullptr");
      return __str_find_last_of<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, __n);
  }

  constexpr inline
  size_type find_last_of(const _CharT* str, size_type __pos=npos) const
  {
      _LIBCPP_ASSERT(str != nullptr, "string_view::find_last_of(): received nullptr");
      return __str_find_last_of<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, traits_type::length(str));
  }

  // find_first_not_of
  constexpr inline
  size_type find_first_not_of(basic_string_view str, size_type __pos=0) const noexcept
  {
      _LIBCPP_ASSERT(str.size() == 0 || str.data() != nullptr, "string_view::find_first_not_of(): received nullptr");
      return __str_find_first_not_of<value_type, size_type, traits_type, npos>
          (data(), size(), str.data(), __pos, str.size());
  }

  constexpr inline
  size_type find_first_not_of(_CharT __c, size_type __pos=0) const noexcept
  {
      return __str_find_first_not_of<value_type, size_type, traits_type, npos>
          (data(), size(), __c, __pos);
  }

  constexpr inline
  size_type find_first_not_of(const _CharT* str, size_type __pos, size_type __n) const
  {
      _LIBCPP_ASSERT(__n == 0 || str != nullptr, "string_view::find_first_not_of(): received nullptr");
      return __str_find_first_not_of<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, __n);
  }

  constexpr inline
  size_type find_first_not_of(const _CharT* str, size_type __pos=0) const
  {
      _LIBCPP_ASSERT(str != nullptr, "string_view::find_first_not_of(): received nullptr");
      return __str_find_first_not_of<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, traits_type::length(str));
  }

  // find_last_not_of
  constexpr inline
  size_type find_last_not_of(basic_string_view str, size_type __pos=npos) const noexcept
  {
      _LIBCPP_ASSERT(str.size() == 0 || str.data() != nullptr, "string_view::find_last_not_of(): received nullptr");
      return __str_find_last_not_of<value_type, size_type, traits_type, npos>
          (data(), size(), str.data(), __pos, str.size());
  }

  constexpr inline
  size_type find_last_not_of(_CharT __c, size_type __pos=npos) const noexcept
  {
      return __str_find_last_not_of<value_type, size_type, traits_type, npos>
          (data(), size(), __c, __pos);
  }

  constexpr inline
  size_type find_last_not_of(const _CharT* str, size_type __pos, size_type __n) const
  {
      _LIBCPP_ASSERT(__n == 0 || str != nullptr, "string_view::find_last_not_of(): received nullptr");
      return __str_find_last_not_of<value_type, size_type, traits_type, npos>
          (data(), size(), str, __pos, __n);
  }

  constexpr inline
  size_type find_last_not_of(const _CharT* __s, size_type __pos=npos) const
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
  { return !empty() && _Traits::eq(front(), __c); }

  constexpr inline
  bool starts_with(const value_type* __s) const noexcept
  { return starts_with(basic_string_view(__s)); }

  constexpr inline
  bool ends_with(basic_string_view __s) const noexcept
  { return size() >= __s.size() && compare(size() - __s.size(), npos, __s) == 0; }

  constexpr inline
  bool ends_with(value_type __c) const noexcept
  { return !empty() && _Traits::eq(back(), __c); }

  constexpr inline
  bool ends_with(const value_type* __s) const noexcept
  { return ends_with(basic_string_view(__s)); }
#endif

}; // class basic_string_view

// [string.view.comparison]
// operator ==
template<class _CharT, class _Traits>
constexpr inline
bool operator==(basic_string_view<_CharT, _Traits> __lhs,
                basic_string_view<_CharT, _Traits> __rhs) noexcept
{
    if ( __lhs.size() != __rhs.size()) return false;
    return __lhs.compare(__rhs) == 0;
}

template<class _CharT, class _Traits>
constexpr inline
bool operator==(basic_string_view<_CharT, _Traits> __lhs,
                std::common_type_t<basic_string_view<_CharT, _Traits>> __rhs) noexcept
{
    if ( __lhs.size() != __rhs.size()) return false;
    return __lhs.compare(__rhs) == 0;
}

template<class _CharT, class _Traits>
constexpr inline
bool operator==(std::common_type_t<basic_string_view<_CharT, _Traits>> __lhs,
                basic_string_view<_CharT, _Traits> __rhs) noexcept
{
    if ( __lhs.size() != __rhs.size()) return false;
    return __lhs.compare(__rhs) == 0;
}


// operator !=
template<class _CharT, class _Traits>
constexpr inline
bool operator!=(basic_string_view<_CharT, _Traits> __lhs, basic_string_view<_CharT, _Traits> __rhs) noexcept
{
    if ( __lhs.size() != __rhs.size())
        return true;
    return __lhs.compare(__rhs) != 0;
}

template<class _CharT, class _Traits>
constexpr inline
bool operator!=(basic_string_view<_CharT, _Traits> __lhs,
                std::common_type_t<basic_string_view<_CharT, _Traits>> __rhs) noexcept
{
    if ( __lhs.size() != __rhs.size())
        return true;
    return __lhs.compare(__rhs) != 0;
}

template<class _CharT, class _Traits>
constexpr inline
bool operator!=(std::common_type_t<basic_string_view<_CharT, _Traits>> __lhs,
                basic_string_view<_CharT, _Traits> __rhs) noexcept
{
  if ( __lhs.size() != __rhs.size())
    return true;
  return __lhs.compare(__rhs) != 0;
}


// operator <
template<class _CharT, class _Traits>
constexpr inline
bool operator<(basic_string_view<_CharT, _Traits> __lhs, basic_string_view<_CharT, _Traits> __rhs) noexcept {
  return __lhs.compare(__rhs) < 0;
}

template<class _CharT, class _Traits>
constexpr inline
bool operator<(basic_string_view<_CharT, _Traits> __lhs,
                std::common_type_t<basic_string_view<_CharT, _Traits>> __rhs) noexcept
{
  return __lhs.compare(__rhs) < 0;
}

template<class _CharT, class _Traits>
constexpr inline
bool operator<(std::common_type_t<basic_string_view<_CharT, _Traits>> __lhs,
                basic_string_view<_CharT, _Traits> __rhs) noexcept
{
  return __lhs.compare(__rhs) < 0;
}


// operator >
template<class _CharT, class _Traits>
constexpr inline
bool operator> (basic_string_view<_CharT, _Traits> __lhs, basic_string_view<_CharT, _Traits> __rhs) noexcept
{
  return __lhs.compare(__rhs) > 0;
}

template<class _CharT, class _Traits>
constexpr inline
bool operator>(basic_string_view<_CharT, _Traits> __lhs,
               std::common_type_t<basic_string_view<_CharT, _Traits>> __rhs) noexcept
{
  return __lhs.compare(__rhs) > 0;
}

template<class _CharT, class _Traits>
constexpr inline
bool operator>(std::common_type_t<basic_string_view<_CharT, _Traits>> __lhs,
               basic_string_view<_CharT, _Traits> __rhs) noexcept
{
  return __lhs.compare(__rhs) > 0;
}


// operator <=
template<class _CharT, class _Traits>
constexpr inline
bool operator<=(basic_string_view<_CharT, _Traits> __lhs, basic_string_view<_CharT, _Traits> __rhs) noexcept
{
  return __lhs.compare(__rhs) <= 0;
}

template<class _CharT, class _Traits>
constexpr inline
bool operator<=(basic_string_view<_CharT, _Traits> __lhs,
                std::common_type_t<basic_string_view<_CharT, _Traits>> __rhs) noexcept
{
  return __lhs.compare(__rhs) <= 0;
}

template<class _CharT, class _Traits>
constexpr inline
bool operator<=(std::common_type_t<basic_string_view<_CharT, _Traits>> __lhs,
                basic_string_view<_CharT, _Traits> __rhs) noexcept
{
  return __lhs.compare(__rhs) <= 0;
}


// operator >=
template<class _CharT, class _Traits>
constexpr inline
bool operator>=(basic_string_view<_CharT, _Traits> __lhs, basic_string_view<_CharT, _Traits> __rhs) noexcept
{
  return __lhs.compare(__rhs) >= 0;
}


template<class _CharT, class _Traits>
constexpr inline
bool operator>=(basic_string_view<_CharT, _Traits> __lhs,
                std::common_type_t<basic_string_view<_CharT, _Traits>> __rhs) noexcept
{
  return __lhs.compare(__rhs) >= 0;
}

template<class _CharT, class _Traits>
constexpr inline
bool operator>=(std::common_type_t<basic_string_view<_CharT, _Traits>> __lhs,
                basic_string_view<_CharT, _Traits> __rhs) noexcept
{
    return __lhs.compare(__rhs) >= 0;
}

#if 0
// TODO(tybl): Define in ostream
template<class _CharT, class _Traits>
std::basic_ostream<_CharT, _Traits>&
operator<<(std::basic_ostream<_CharT, _Traits>& __os,
           basic_string_view<_CharT, _Traits> str);
#endif

typedef basic_string_view<char>     string_view;
typedef basic_string_view<char8_t>  u8string_view;
typedef basic_string_view<char16_t> u16string_view;
typedef basic_string_view<char32_t> u32string_view;
typedef basic_string_view<wchar_t>  wstring_view;

#if 0
// [string.view.hash]
template<class _CharT>
struct hash<basic_string_view<_CharT, std::char_traits<_CharT>>>
    : public unary_function<basic_string_view<_CharT, std::char_traits<_CharT> >, size_t>
{
    inline
    size_t operator()(const basic_string_view<_CharT, std::char_traits<_CharT> > __val) const noexcept {
        return __do_string_hash(__val.data(), __val.data() + __val.size());
    }
};
#endif

inline namespace literals {

  inline namespace string_view_literals {

    inline constexpr
    basic_string_view<char> operator "" _sv(const char *str, size_t __len) noexcept {
      return basic_string_view<char>(str, __len);
    }

    inline constexpr
    basic_string_view<wchar_t> operator "" _sv(const wchar_t *str, size_t __len) noexcept {
      return basic_string_view<wchar_t>(str, __len);
    }

    inline constexpr
    basic_string_view<char8_t> operator "" _sv(const char8_t *str, size_t __len) noexcept {
      return basic_string_view<char8_t>(str, __len);
    }

    inline constexpr
    basic_string_view<char16_t> operator "" _sv(const char16_t *str, size_t __len) noexcept {
      return basic_string_view<char16_t>(str, __len);
    }

    inline constexpr
    basic_string_view<char32_t> operator "" _sv(const char32_t *str, size_t __len) noexcept {
      return basic_string_view<char32_t>(str, __len);
    }

  } // inline namespace string_view_literals

} // inline namespace literals

} // namespace tybl::vodka

#endif // TYBL_VODKA_STRINGVIEW_BASICSTRINGVIEW_HPP

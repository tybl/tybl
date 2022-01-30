// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_BASICFIXEDSTRING_HPP
#define TYBL_VODKA_BASICFIXEDSTRING_HPP

namespace tybl::vodka {

template <typename CharType, size_t Size>
struct basic_fixed_string {
  CharType m_buffer[Size + 1];

  explicit constexpr basic_fixed_string(CharType const* p_str) {
    for (unsigned i = 0; i != Size; ++i) {
      m_buffer[i] = p_str[i];
    }
  }

  [[nodiscard]] constexpr size_t size() const noexcept { return Size; }

  [[nodiscard]] explicit constexpr operator CharType const*() const { return m_buffer; }

}; // struct basic_fixed_string

template <typename CharType, size_t Size>
basic_fixed_string(CharType const (&)[Size]) -> basic_fixed_string<CharType, Size - 1>;

} // namespace tybl::vodka

#endif // TYBL_VODKA_BASICFIXEDSTRING_HPP

// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_BASICFIXEDSTRING_HPP
#define TYBL_VODKA_BASICFIXEDSTRING_HPP

#include <cstddef>

namespace tybl::vodka {

template <typename CharType, size_t Size>
struct basic_fixed_string {

  CharType m_buffer[Size + 1];

  [[nodiscard]] constexpr size_t size() const noexcept { return Size; }

  [[nodiscard]] explicit constexpr operator CharType const*() const noexcept { return m_buffer; }

}; // struct basic_fixed_string

template <typename CharType, size_t Size>
basic_fixed_string(CharType const (&)[Size]) -> basic_fixed_string<CharType, Size - 1>;

} // namespace tybl::vodka

#endif // TYBL_VODKA_BASICFIXEDSTRING_HPP

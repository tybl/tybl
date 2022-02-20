// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_BASICFIXEDSTRING_HPP
#define TYBL_VODKA_BASICFIXEDSTRING_HPP

#include <array>
#include <cstddef>
#include <string_view>

namespace tybl::vodka {

template <typename CharType, size_t Size>
struct basic_fixed_string {

  std::array<CharType, Size + 1> m_buffer;

  [[nodiscard]] constexpr auto size() const noexcept -> size_t { return Size; }

  [[nodiscard]] explicit constexpr operator CharType const*() const noexcept { return m_buffer.data(); }

  [[nodiscard]] explicit constexpr operator std::string_view() const noexcept { return { m_buffer.data(), Size }; }

}; // struct basic_fixed_string

template <typename CharType, size_t Size>
basic_fixed_string(CharType const (&)[Size]) -> basic_fixed_string<CharType, Size - 1>;

} // namespace tybl::vodka

#endif // TYBL_VODKA_BASICFIXEDSTRING_HPP

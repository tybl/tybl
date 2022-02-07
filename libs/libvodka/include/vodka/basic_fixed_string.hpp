// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_BASICFIXEDSTRING_HPP
#define TYBL_VODKA_BASICFIXEDSTRING_HPP

#include <vodka/string_view/basic_string_view.hpp>

#include <cstddef>

namespace tybl::vodka {

template <typename CharType, size_t Size>
struct basic_fixed_string {

  CharType m_buffer[Size + 1];

  [[nodiscard]] constexpr auto size() const noexcept -> size_t { return Size; }

  [[nodiscard]] explicit constexpr operator CharType const*() const noexcept { return m_buffer; }

  [[nodiscard]] explicit constexpr operator std::string_view() const noexcept { return { static_cast<const char*>(m_buffer), Size }; }

}; // struct basic_fixed_string

template <typename CharType, size_t Size>
basic_fixed_string(CharType const (&)[Size]) -> basic_fixed_string<CharType, Size - 1>;

} // namespace tybl::vodka

#endif // TYBL_VODKA_BASICFIXEDSTRING_HPP

// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_STRINGRANGE_HPP
#define TYBL_VODKA_STRINGRANGE_HPP

namespace tybl::vodka {

template <typename CharType>
struct string_range {
  CharType const* m_begin;
  CharType const* m_end;
}; // struct string_range

} // namespace tybl::vodka

#endif // TYBL_VODKA_STRINGRANGE_HPP
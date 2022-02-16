//
#pragma once
#ifndef TYBL_PARSE_CHARACTER_HPP
#define TYBL_PARSE_CHARACTER_HPP

#include <string_view>

namespace tybl::parse {

template <char Char>
auto character(std::string_view& p_in) -> bool {
  bool result = (!p_in.empty() && Char == p_in.front());
  p_in.remove_prefix(static_cast<std::string_view::size_type>(result));
  return result;
}

} // namespace tybl::parse

#endif // TYBL_PARSE_CHARACTER_HPP
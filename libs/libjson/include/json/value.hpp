// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_JSON_VALUE_HPP
#define TYBL_JSON_VALUE_HPP

#include <map>
#include <string_view>
#include <variant>
#include <vector>

namespace tybl::json {

struct value : public std::variant<std::string_view, std::vector<value>, std::map<std::string_view, value>> {
  using Base = std::variant<std::string_view, std::vector<value>, std::map<std::string_view, value>>;
  using Base::operator=;
  using Base::Base;
};

} // namespace tybl::json

#endif // TYBL_JSON_VALUE_HPP

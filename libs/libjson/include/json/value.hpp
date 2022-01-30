// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_JSON_VALUE_HPP
#define TYBL_JSON_VALUE_HPP

#include <vodka/string_view/basic_string_view.hpp>

#include <map>
#include <variant>
#include <vector>

namespace tybl::json {

struct value : public std::variant<tybl::vodka::string_view, std::vector<value>, std::map<tybl::vodka::string_view, value>> {
  using Base = std::variant<tybl::vodka::string_view, std::vector<value>, std::map<tybl::vodka::string_view, value>>;
  using Base::operator=;
  using Base::Base;
};

} // namespace tybl::json

#endif // TYBL_JSON_VALUE_HPP

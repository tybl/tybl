// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef VODKA_JSON_VALUE_HPP
#define VODKA_JSON_VALUE_HPP

#include <map>
#include <string_view>
#include <variant>
#include <vector>

namespace vodka::json {

struct value
  : public std::variant<std::string_view, std::vector<value>, std::map<std::string_view, value>>
{
   using Base = std::variant<std::string_view, std::vector<value>, std::map<std::string_view, value>>;
   using Base::operator=;
   using Base::Base;
};

} // namespace vodka::json

#endif // VODKA_JSON_VALUE_HPP

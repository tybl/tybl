// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef _TYBL__JSON__VALUE__HPP_
#define _TYBL__JSON__VALUE__HPP_

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

#endif // _TYBL__JSON__VALUE__HPP_

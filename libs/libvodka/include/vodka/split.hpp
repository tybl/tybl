#pragma once
#ifndef TYBL_VODKA_SPLIT_HPP
#define TYBL_VODKA_SPLIT_HPP

#include <string_view>
#include <vector>

namespace tybl::vodka {

auto split(std::string_view p_input_str, char p_delimiter) -> std::vector<std::string_view> {
  std::vector<std::string_view> result;
  auto end_index = p_input_str.find(p_delimiter);
  while (std::string_view::npos != end_index) {
    result.emplace_back(p_input_str.data(), end_index);
    p_input_str = p_input_str.substr(end_index + 1);
    end_index = p_input_str.find(p_delimiter);
  }
  result.emplace_back(p_input_str.data(), p_input_str.size());
  return result;
}

} // namespace tybl::vodka

#endif // TYBL_VODKA_SPLIT_HPP
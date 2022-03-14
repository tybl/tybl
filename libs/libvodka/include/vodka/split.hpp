#pragma once
#ifndef TYBL_VODKA_SPLIT_HPP
#define TYBL_VODKA_SPLIT_HPP

#include <algorithm>
#include <string_view>
#include <vector>

namespace tybl::vodka {

auto split(std::string_view p_str, char p_delim) -> std::vector<std::string_view> {
  std::vector<std::string_view> result;
  result.reserve(1UL + static_cast<size_t>(std::count(p_str.begin(), p_str.end(), p_delim)));
  for (auto index = p_str.find(p_delim); index != std::string_view::npos; index = p_str.find(p_delim)) {
    result.emplace_back(p_str.data(), index);
    p_str = p_str.substr(index + 1);
  }
  result.emplace_back(p_str.data(), p_str.size());
  return result;
}

} // namespace tybl::vodka

#endif // TYBL_VODKA_SPLIT_HPP

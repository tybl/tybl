#pragma once
#ifndef TYBL_VODKA_SPLITON_HPP
#define TYBL_VODKA_SPLITON_HPP

#include <algorithm>   // std::find, std::find_first_of
#include <string_view>
#include <vector>

namespace tybl::vodka {

template <typename InputIt, typename FwdIt, typename BinOp>
void tokenize_on(InputIt first, InputIt last, FwdIt first_delim, FwdIt last_delim, BinOp binary_operation) {
  while (first != last) {
    const auto pos = std::find_first_of(first, last, first_delim, last_delim);
    binary_operation(first, pos);
    if (pos == last) { break; }
    first = std::next(pos);
  }
}

inline auto split_on(std::string_view p_str, char p_delim) -> std::vector<std::string_view> {
  std::vector<std::string_view> result;
  auto const* first_p = std::cbegin(p_str);
  auto const* last_p = std::cend(p_str);
  auto const* pos_p = first_p;
  do {
    pos_p = std::find(first_p, last_p, p_delim);
    result.emplace_back(first_p, pos_p);
    first_p = std::next(pos_p);
  } while (last_p != pos_p);
  return result;
}

inline auto split_on_a(std::string_view p_str, char p_delim) -> std::vector<std::string_view> {
  std::vector<std::string_view> result;
  //result.reserve(std::size(p_str));
  auto const* first_p = std::cbegin(p_str);
  auto const* last_p = std::cend(p_str);
  auto const* pos_p = std::find(first_p, last_p, p_delim);
  while (last_p != pos_p) {
    //result.emplace_back(first_p, pos_p);
    first_p = std::next(pos_p);
    pos_p = std::find(first_p, last_p, p_delim);
  }
  //result.emplace_back(first_p, last_p);
  return result;
}

#if 0
auto split_on_any_of(std::string_view p_str, std::string_view p_delims) -> std::vector<std::string_view> {
  std::vector<std::string_view> result;
  result.reserve(p_str.size());
  const auto *first_p = p_str.cbegin();
  const auto *last_p = p_str.cend();
  const auto *pos_p = std::find_first_of(first_p, last_p, p_delims.cbegin(), p_delims.cend());
  while (last_p != pos_p) {
    result.emplace_back(first_p, pos_p);
    first_p = std::next(pos_p);
    pos_p = std::find_first_of(first_p, last_p, p_delims.cbegin(), p_delims.cend());
  }
  result.emplace_back(first_p, last_p);
  return result;
}
#endif

} // namespace tybl::vodka

#endif // TYBL_VODKA_SPLITON_HPP
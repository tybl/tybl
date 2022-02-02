// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_PARM_PARAMETER_HPP
#define TYBL_PARM_PARAMETER_HPP

#include <numeric>
#include <string>
#include <vector>

namespace parm {

class argument {
  friend class Application;

  std::vector<std::string> m_names;
  std::string m_help;

public:
  // Ref: https://stackoverflow.com/questions/13978916/inserting-a-variadic-argument-list-into-a-vector
  template <typename... Args>
  argument(Args... p_arguments)
    : m_names{p_arguments...} {}

  // For printing usage
  auto help(std::string_view p_help) {
    m_help = p_help;
    return *this;
  }

private:
  // For printing usage
  [[nodiscard]] auto length() const -> size_t {
    return std::accumulate(std::begin(m_names), std::end(m_names), size_t(0), [](const auto& p_sum, const auto& p_string) {
      return p_sum + p_string.size() + 1; // +1 for space between names
    });
  }
}; // class argument

} // namespace parm

#endif // TYBL_PARM_PARAMETER_HPP

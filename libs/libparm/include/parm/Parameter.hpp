// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_PARM_PARAMETER_HPP
#define TYBL_PARM_PARAMETER_HPP

#include <numeric>
#include <string>
#include <vector>

namespace parm {

class Argument {
  friend class Application;

  std::vector<std::string> mNames;
  std::string mHelp;
public:
  // Ref: https://stackoverflow.com/questions/13978916/inserting-a-variadic-argument-list-into-a-vector
  template <typename... Args>
  Argument(Args... args)
    : mNames{args...} {}

  // For printing usage
  auto help(std::string_view help) {
    mHelp = help;
    return *this;
  }

private:
  // For printing usage
  size_t length() const {
    return std::accumulate(std::begin(mNames), std::end(mNames), size_t(0),
      [](const auto &sum, const auto &s) {
        return sum + s.size() + 1; // +1 for space between names
      });
  }
}; // class Argument

} // namespace parm

#endif // TYBL_PARM_PARAMETER_HPP

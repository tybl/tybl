// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_PARM_APPLICATION_HPP
#define TYBL_PARM_APPLICATION_HPP

#include "Parameter.hpp"

#include <list>
#include <map>
#include <string>
#include <string_view>

namespace parm {

class Application {
  std::string mName;        // For printing usage
  std::string mVersion;     // For printing usage
  std::string mDescription; // For printing usage
  std::string mEpilog;      // For printing usage

  // std::list prevents iterators from being invalidated
  using list_iterator = std::list<Argument>::iterator;
  std::list<Argument> mArguments;

  // std::map or std::unordered_map could be used
  // TODO: Investigate performance characteristics of either
  std::map<std::string_view, list_iterator> mArgumentMap;

public:
  Application(std::string pName, std::string pVersion);

  // Ref: https://www.modernescpp.com/index.php/c-core-guidelines-rules-for-variadic-templates
  template <typename... Args>
  auto add_argument(Args&&... args) -> Argument&;

  auto run(int, char const**) -> int;

private:
  void parse_arguments(std::vector<std::string> const& /*args*/);

  // For printing usage
  size_t longest_argument_length() const;

  void index_argument(list_iterator pArgIt);

}; // class Application

// Ref: https://www.modernescpp.com/index.php/c-core-guidelines-rules-for-variadic-templates
template <typename... Args>
auto Application::add_argument(Args&&... args) -> Argument& {
  auto arg_it = mArguments.emplace(std::cend(mArguments), std::forward<Args>(args)...);
  index_argument(arg_it);
  return *arg_it;
}

} // namespace parm

#endif // TYBL_PARM_APPLICATION_HPP

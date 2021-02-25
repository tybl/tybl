// License: The Unlicense (https://unlicense.org)
#ifndef PARM_APPLICATION_HPP
#define PARM_APPLICATION_HPP

#include "Parameter.hpp"

#include <list>
#include <map>
#include <string>

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

  Application(std::string pName, std::string pVersion)
    : mName(pName)
    , mVersion(pVersion)
  {
    add_argument("-h", "--help")
      .help("shows help message and exits");
    add_argument("-v", "--version")
      .help("prints version information and exits");
  }

  // Ref: https://www.modernescpp.com/index.php/c-core-guidelines-rules-for-variadic-templates
  template <typename... Args>
  auto add_argument(Args&&... args) -> Argument& {
    auto arg_it =
      mArguments.emplace(std::cend(mArguments), std::forward<Args>(args)...);
    index_argument(arg_it);
    return *arg_it;
  }

  auto run(int, char const**) -> int {
    // 1. Parse arguments
    // 2. Invoke commands
    return 0;
  }

private:
  void parse_arguments(std::vector<std::string> const& /*args*/) {
    // 1. Ignore first argument, as it is the name that invoked the program
    // 2. For each of the argument_strings in args,
    //  a. Check if the argument_string is a positional argument
    //  b. Check if the argument_string is a defined parameter
    //  c. Check if the argument_string consists of multiple defined parameters
    //     in a compound argument
    //  d. Print an error and usage.
  }

  // For printing usage
  size_t longest_argument_length() const {
    return std::accumulate(mArgumentMap.cbegin(), mArgumentMap.cend(), 0ULL,
      [](size_t m, auto const& r) { return std::max(m, r.second->length()); });
  }

  void index_argument(list_iterator pArgIt) {
    for (auto const& name : pArgIt->mNames) {
      mArgumentMap.insert_or_assign(name, pArgIt);
    }
  }
}; // class Application

} // namespace parm

#endif // PARM_APPLICATION_HPP

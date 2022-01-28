// License: The Unlicense (https://unlicense.org)
#include <parm/Application.hpp>

#include "parm/Parameter.hpp"

#include <vodka/algorithm/max.hpp>

#include <list>
#include <map>
#include <string>

namespace parm {

Application::Application(std::string pName, std::string pVersion)
  : mName(pName)
  , mVersion(pVersion) {
  add_argument("-h", "--help").help("shows help message and exits");
  add_argument("-v", "--version").help("prints version information and exits");
}

auto Application::run(int, char const**) -> int {
  // 1. Parse arguments
  // 2. Invoke commands
  return 0;
}

void Application::parse_arguments(std::vector<std::string> const& /*args*/) {
  // 1. Ignore first argument, as it is the name that invoked the program
  // 2. For each of the argument_strings in args,
  //  a. Check if the argument_string is a positional argument
  //  b. Check if the argument_string is a defined parameter
  //  c. Check if the argument_string consists of multiple defined parameters
  //     in a compound argument
  //  d. Print an error and usage.
}

// For printing usage
size_t Application::longest_argument_length() const {
  return std::accumulate(mArgumentMap.cbegin(), mArgumentMap.cend(), 0ULL,
                         [](size_t m, auto const& r) { return tybl::vodka::max(m, r.second->length()); });
}

void Application::index_argument(list_iterator pArgIt) {
  for (auto const& name : pArgIt->mNames) {
    mArgumentMap.insert_or_assign(name, pArgIt);
  }
}

} // namespace parm

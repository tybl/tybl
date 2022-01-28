// License: The Unlicense (https://unlicense.org)
#include <parm/Application.hpp>

#include "parm/Parameter.hpp"

#include <vodka/algorithm/max.hpp>

#include <list>
#include <map>
#include <string>

namespace parm {

Application::Application(std::string const& p_name, std::string const& p_version)
  : m_name(p_name)
  , m_version(p_version) {
  add_argument("-h", "--help").help("shows help message and exits");
  add_argument("-v", "--version").help("prints version information and exits");
}

auto Application::run(int, char const**) -> int {
  // TODO(tybl):
  // 1. Parse arguments
  // 2. Invoke commands
  return 0;
}

void Application::parse_arguments(std::vector<std::string> const& /*p_args*/) {
  // TODO(tybl):
  // 1. Ignore first argument, as it is the name that invoked the program
  // 2. For each of the argument_strings in p_args,
  //  a. Check if the argument_string is a positional argument
  //  b. Check if the argument_string is a defined parameter
  //  c. Check if the argument_string consists of multiple defined parameters
  //     in a compound argument
  //  d. Print an error and usage.
}

// For printing usage
size_t Application::longest_argument_length() const {
  return std::accumulate(m_argument_map.cbegin(), m_argument_map.cend(), 0ULL,
                         [](size_t p_max_length, auto const& p_argument_entry) { return tybl::vodka::max(p_max_length, p_argument_entry.second->length()); });
}

void Application::index_argument(list_iterator p_argument_iterator) {
  for (auto const& name : p_argument_iterator->m_names) {
    m_argument_map.insert_or_assign(name, p_argument_iterator);
  }
}

} // namespace parm

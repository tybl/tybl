// License: The Unlicense (https://unlicense.org)
#ifndef COCLES_LEDGER_UTIL_STRINGIFY_ARGUMENTS_HPP
#define COCLES_LEDGER_UTIL_STRINGIFY_ARGUMENTS_HPP

#include <string>
#include <vector>

namespace ledger {

namespace util {

std::vector<std::string> stringify_arguments(int argc, const char* argv[]);

} // namespace util

} // namespace ledger

#endif // COCLES_LEDGER_UTIL_STRINGIFY_ARGUMENTS_HPP

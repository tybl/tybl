// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COCLES_LEDGER_UTIL_STRINGIFYARGUMENTS_HPP
#define TYBL_COCLES_LEDGER_UTIL_STRINGIFYARGUMENTS_HPP

#include <string>
#include <vector>

namespace ledger {

namespace util {

std::vector<std::string> stringify_arguments(int argc, const char* argv[]);

} // namespace util

} // namespace ledger

#endif // TYBL_COCLES_LEDGER_UTIL_STRINGIFYARGUMENTS_HPP

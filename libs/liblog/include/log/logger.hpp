// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef _TYBL__LOG__LOGGER__HPP_
#define _TYBL__LOG__LOGGER__HPP_

#include <iosfwd>
#include <source_location>
#include <string>

namespace tybl::log {

std::ostream& log();
// TODO(tybl): std::ostream& log(std::source_location p_source_location = std::source_location::current());

} // namespace tybl::log

#endif // _TYBL__LOG__LOGGER__HPP_

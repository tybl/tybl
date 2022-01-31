// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LOG_LOGGER_HPP
#define TYBL_LOG_LOGGER_HPP

#include <iosfwd>
#include <source_location>
#include <string>

namespace tybl::log {

auto log() -> std::ostream&;
// TODO(tybl): std::ostream& log(std::source_location p_source_location = std::source_location::current());

} // namespace tybl::log

#endif // TYBL_LOG_LOGGER_HPP
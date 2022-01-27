// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef _TYBL__LOG__LOGGER__HPP_
#define _TYBL__LOG__LOGGER__HPP_

#include <iosfwd>
#include <string>

namespace tybl::log {

std::ostream& log(std::string const& p_output, uint32_t p_line_number);

} // namespace tybl::log

#endif // _TYBL__LOG__LOGGER__HPP_

// License: The Unlicense (https://unlicense.org)
#include <log/logger.hpp>

#include <iostream>

namespace tybl::log {

std::ostream& log(std::string const& p_output, uint32_t p_line_number) {
  return std::cout << p_output << ": " << p_line_number;
}

} // namespace tybl::log
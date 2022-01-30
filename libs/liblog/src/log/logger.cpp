// License: The Unlicense (https://unlicense.org)
#include <log/logger.hpp>

#include <iostream>

namespace tybl::log {

std::ostream& log() {
  return std::cout;
}

// TODO(tybl): std::ostream& log(const std::source_location p_source_location) { return std::cout; }

} // namespace tybl::log
// License: The Unlicense (https://unlicense.org)
#include <log/logger.hpp>

#include <unistd.h>

namespace tybl::log {

void log(std::string const& p_output) {
  ::write(STDOUT_FILENO, p_output.data(), p_output.size());
}

} // namespace tybl::log
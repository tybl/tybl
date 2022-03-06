// License: The Unlicense (https://unlicense.org)
#include <nmea/serial_configuration.hpp>

#include <fmt/core.h>

namespace tybl::nmea {

auto serial_configuration::to_string() -> std::string {
  return fmt::format("1,{},{},{},{}", baud, data_bits, stop_bits, parity);
}

} // namespace tybl::nmea
// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_SERIALCONFIGURATION_HPP
#define TYBL_NMEA_SERIALCONFIGURATION_HPP

#include <nmea/command.hpp>

namespace tybl::nmea {

struct serial_configuration : public command {
  int32_t baud{4800};   // 4800, 9600, 19200, 38400
  int32_t data_bits{8}; // 7, 8 Databits
  int32_t stop_bits{1}; // 0, 1 Stopbits
  int32_t parity{0};    // 0=none, 1=odd, 2=even Parity

  serial_configuration()
    : command("PSRF100") {}

  auto to_string() -> std::string override;

}; // struct serial_configuration

} // namespace tybl::nmea

#endif // TYBL_NMEA_SERIALCONFIGURATION_HPP
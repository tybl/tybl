// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_COMMAND_HPP
#define TYBL_NMEA_COMMAND_HPP

#include <cstdint>
#include <string>

namespace tybl::nmea {

class command {
  // TODO(tybl): This struct doesn't contain the functionality to maintain
  // the invariants inherent to it. That makes it difficult to know how to
  // properly build it.
  std::string m_message;
  std::string m_name;
  // TODO(tybl): Should the checksum be an unsigned char? Or better: std::byte
  uint8_t m_checksum{};

public:
  command();

  explicit command(std::string p_name);

  virtual ~command();

  virtual auto to_string() -> std::string;

  auto add_checksum(std::string const& p_s) -> std::string;

}; // struct command

} // namespace tybl::nmea

#endif // TYBL_NMEA_COMMAND_HPP
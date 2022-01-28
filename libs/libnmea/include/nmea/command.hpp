// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_COMMAND_HPP
#define TYBL_NMEA_COMMAND_HPP

#include "nmea/Parser.hpp"

#include <string>

namespace nmea {

class command {
  // TODO(tybl): This struct doesn't contain the functionality to maintain
  // the invariants inherent to it. That makes it difficult to know how to
  // properly build it.
  std::string m_message;
  std::string m_name;
  // TODO(tybl): Should the checksum be an unsigned char?
  uint8_t m_checksum;

public:
  command();

  command(std::string const& p_name);

  virtual ~command();

  virtual std::string to_string();

  std::string add_checksum(std::string const& p_s);

}; // struct command

} // namespace nmea

#endif // TYBL_NMEA_COMMAND_HPP
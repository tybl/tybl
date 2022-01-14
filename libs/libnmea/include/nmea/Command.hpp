#pragma once

#include "nmea/Parser.hpp"

#include <string>

namespace nmea {

class Command {
  // TODO(tybl): This struct doesn't contain the functionality to maintain
  // the invariants inherent to it. That makes it difficult to know how to
  // properly build it.
  std::string m_message;
  std::string m_name;
  // TODO(tybl): Should the checksum be an unsigned char?
  uint8_t m_checksum;
public:

  Command();

  Command(std::string name);

  virtual ~Command();

  virtual std::string to_string();

  std::string add_checksum(std::string s);

}; // struct Command

} // namespace nmea

// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_SENTENCE_HPP
#define TYBL_NMEA_SENTENCE_HPP

#include <string>
#include <vector>

namespace nmea {

class Parser;

class sentence {
  friend Parser;
  bool m_is_valid;

public:
  std::string text;                    // whole plaintext of the received command
  std::string name;                    // name of the command
  std::vector<std::string> parameters; // list of parameters from the command
  std::string checksum;
  bool m_is_checksum_calculated;
  uint8_t m_parsed_checksum;
  uint8_t m_calculated_checksum;

  enum MessageID { // These m_id's are according to NMEA standard.
    Unknown = -1,
    GGA = 0,
    GLL = 1,
    GSA = 2,
    GSV = 3,
    RMC = 4,
    VTG = 5, // notice missing 6,7
    ZDA = 8
  };
  sentence();

  virtual ~sentence();

  auto is_checksum_ok() const -> bool;

  auto valid() const -> bool;

}; // class sentence

} // namespace nmea

#endif // TYBL_NMEA_SENTENCE_HPP

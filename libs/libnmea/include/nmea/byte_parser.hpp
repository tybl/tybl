// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_BYTEPARSER_HPP
#define TYBL_NMEA_BYTEPARSER_HPP

#include <nmea/sentence_parser.hpp>

namespace tybl::nmea {

struct byte_parser : public sentence_parser {
  void read_byte(char p_b);

  void read_buffer(std::string_view p_buffer);

  void read_line(std::string p_line);

private:
  std::string m_buffer;
  bool m_filling_buffer{false};
  static constexpr size_t MAX_BUFFER_SIZE = 2000;
}; // class byte_parser

} // namespace tybl::nmea

#endif // TYBL_NMEA_BYTEPARSER_HPP
// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_PARSER_HPP
#define TYBL_NMEA_PARSER_HPP

#include <nmea/event.hpp>
#include <nmea/sentence.hpp>

#include <cstdint>
#include <functional>
#include <numeric>
#include <string>
#include <string_view>
#include <unordered_map>

namespace tybl::nmea {

class sentence_parser {
  std::unordered_map<std::string, std::function<void(sentence)>> m_event_table;
  std::string m_buffer;
  uint32_t m_max_buffer_size{2000}; // limit the max size if no newline ever comes... Prevents
                                    // huge m_buffer string internally
  bool m_filling_buffer{false};

  // fills the given NMEA sentence with the results of parsing the string.
  void parse_text(sentence& p_nmea, std::string p_text);

public:
  Event<void(sentence const&)> on_sentence; // called every time sentence_parser receives any NMEA sentence

  // one handler called for any named sentence where name is the "p_cmd_key"
  void set_sentence_handler(std::string const& p_cmd_key, std::function<void(sentence const&)> const& p_handler);

  // This function expects the data to be a single line with an actual sentence in it, else it throws an error.
  void read_sentence(std::string p_cmd); // called when sentence_parser receives a sentence from the byte stream. Can
                                         // also be called by user to inject sentences.

  [[gnu::pure]] static auto calc_checksum(std::string const& /*p_s*/) -> uint8_t; // returns checksum of string -- XOR

}; // class sentence_parser

} // namespace tybl::nmea

#endif // TYBL_NMEA_PARSER_HPP
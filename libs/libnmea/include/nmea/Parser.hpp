// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_PARSER_HPP
#define TYBL_NMEA_PARSER_HPP

#include "nmea/Event.hpp"
#include "nmea/sentence.hpp"

#include <cstdint>
#include <functional>
#include <numeric>
#include <string>
#include <string_view>
#include <unordered_map>

namespace nmea {

class Parser {
  std::unordered_map<std::string, std::function<void(sentence)>> m_event_table;
  std::string m_buffer;
  uint32_t m_max_buffer_size; // limit the max size if no newline ever comes... Prevents huge m_buffer string internally
  bool m_filling_buffer;

  void parse_text(sentence& p_nmea,
                  std::string p_s); // fills the given NMEA sentence with the results of parsing the string.

  void on_info(sentence& p_n, std::string const& p_s) const;
  void on_warn(sentence& p_n, std::string const& p_s) const;
  void on_err(sentence& p_n, std::string const& p_s);

public:
  Parser();

  virtual ~Parser();

  bool log;

  Event<void(const sentence&)> on_sentence; // called every time parser receives any NMEA sentence
  void set_sentence_handler(std::string p_cmd_key,
                            std::function<void(const sentence&)>
                                p_handler);    // one handler called for any named sentence where name is the "cmdKey"
  std::string get_list_of_sentence_handlers() const; // show a list of message names that currently have m_handlers.

  // Byte streaming functions
  void read_byte(char p_b);

  void read_buffer(char* p_b, uint32_t p_size);

  void read_line(std::string p_line);

  // This function expects the data to be a single line with an actual sentence in it, else it throws an error.
  void read_sentence(std::string p_cmd); // called when parser receives a sentence from the byte stream. Can also be
                                         // called by user to inject sentences.

  static uint8_t calc_checksum(std::string const&); // returns checksum of string -- XOR

}; // class Parser

} // namespace nmea

#endif // TYBL_NMEA_PARSER_HPP
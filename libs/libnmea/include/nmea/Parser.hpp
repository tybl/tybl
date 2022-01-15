#pragma once

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
  std::unordered_map<std::string, std::function<void(sentence)>> eventTable;
  std::string m_buffer;
  uint32_t maxbuffersize; // limit the max size if no newline ever comes... Prevents huge m_buffer string internally
  bool m_fillingbuffer;

  void parse_text(sentence& nmea, std::string s);    //fills the given NMEA sentence with the results of parsing the string.

  void on_info(sentence& n, std::string s);
  void on_warn(sentence& n, std::string s);
  void on_err(sentence& n, std::string s);
public:

  Parser();

  virtual ~Parser();

  bool log;

  Event<void(const sentence&)> onSentence;        // called every time parser receives any NMEA sentence
  void set_sentence_handler(std::string cmdKey, std::function<void(const sentence&)> handler);  //one handler called for any named sentence where name is the "cmdKey"
  std::string get_list_of_sentence_handlers();                          // show a list of message names that currently have handlers.

  // Byte streaming functions
  void read_byte(char b);

  void read_buffer(char* b, uint32_t size);

  void read_line(std::string line);

  // This function expects the data to be a single line with an actual sentence in it, else it throws an error.
  void read_sentence(std::string cmd);        // called when parser receives a sentence from the byte stream. Can also be called by user to inject sentences.

  static uint8_t calc_checksum(std::string);    // returns checksum of string -- XOR

}; // class Parser

} // namespace nmea

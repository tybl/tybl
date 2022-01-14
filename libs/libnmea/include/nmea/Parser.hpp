#pragma once

#include "nmea/Event.hpp"
#include "nmea/Sentence.hpp"

#include <cstdint>
#include <functional>
#include <numeric>
#include <string>
#include <string_view>
#include <unordered_map>

namespace nmea {

class Parser {
  std::unordered_map<std::string, std::function<void(Sentence)>> eventTable;
  std::string buffer;
  uint32_t maxbuffersize; // limit the max size if no newline ever comes... Prevents huge buffer string internally
  bool m_fillingbuffer;

  void parse_text(Sentence& nmea, std::string s);    //fills the given NMEA sentence with the results of parsing the string.

  void on_info(Sentence& n, std::string s);
  void on_warn(Sentence& n, std::string s);
  void on_err(Sentence& n, std::string s);
public:

  Parser();

  virtual ~Parser();

  bool log;

  Event<void(const Sentence&)> onSentence;        // called every time parser receives any NMEA sentence
  void set_sentence_handler(std::string cmdKey, std::function<void(const Sentence&)> handler);  //one handler called for any named sentence where name is the "cmdKey"
  std::string get_list_of_sentence_handlers();                          // show a list of message names that currently have handlers.

  // Byte streaming functions
  void read_byte(uint8_t b);

  void read_buffer(uint8_t* b, uint32_t size);

  void read_line(std::string line);

  // This function expects the data to be a single line with an actual sentence in it, else it throws an error.
  void read_sentence(std::string cmd);        // called when parser receives a sentence from the byte stream. Can also be called by user to inject sentences.

  static uint8_t calc_checksum(std::string);    // returns checksum of string -- XOR

}; // class Parser

} // namespace nmea

#pragma once

#include "nmea/Event.hpp"
#include "nmea/Sentence.hpp"

#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>

namespace nmea {

class Parser {
  std::unordered_map<std::string, std::function<void(Sentence)>> eventTable;
  std::string buffer;
  bool m_fillingbuffer;
  uint32_t maxbuffersize; // limit the max size if no newline ever comes... Prevents huge buffer string internally

  void parseText(Sentence& nmea, std::string s);    //fills the given NMEA sentence with the results of parsing the string.

  void onInfo(Sentence& n, std::string s);
  void onWarning(Sentence& n, std::string s);
  void onError(Sentence& n, std::string s);
public:

  Parser();

  virtual ~Parser();

  bool log;

  Event<void(const Sentence&)> onSentence;        // called every time parser receives any NMEA sentence
  void setSentenceHandler(std::string cmdKey, std::function<void(const Sentence&)> handler);  //one handler called for any named sentence where name is the "cmdKey"
  std::string getRegisteredSentenceHandlersCSV();                          // show a list of message names that currently have handlers.

  // Byte streaming functions
  void readByte(uint8_t b);

  void readBuffer(uint8_t* b, uint32_t size);

  void readLine(std::string line);

  // This function expects the data to be a single line with an actual sentence in it, else it throws an error.
  void readSentence  (std::string cmd);        // called when parser receives a sentence from the byte stream. Can also be called by user to inject sentences.

  static uint8_t calculateChecksum(std::string);    // returns checksum of string -- XOR

}; // class Parser

} // namespace nmea

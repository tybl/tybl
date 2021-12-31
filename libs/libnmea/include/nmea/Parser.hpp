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

class GpggaSentence {
  std::string m_utc;
  std::string m_lat;
  std::string m_lat_dir;
  std::string m_lon;
  std::string m_lon_dir;
  std::string m_quality;
  std::string m_num_satellites;
  std::string m_horizontal_dilution;
  std::string m_altitude;
  std::string m_altitude_units;
  std::string m_undulation;
  std::string m_undulation_units;
  std::string m_age;
  std::string m_station_id;
  std::string m_checksum;
public:
  uint8_t m_calc_checksum;
}; // class GpgaaSentence

class SentenceParser {
  std::unordered_map<std::string_view, std::function<void(Sentence)>> m_parsers;
public:

  void read(std::string sentence) {
    std::string_view sv = sentence;
    GpggaSentence sen10ce;
    auto checksum_pos = sv.find_last_of('*');
    bool has_checksum = checksum_pos != std::string_view::npos;
    if (has_checksum) {
      sen10ce.m_calc_checksum = calculate_checksum(sv.substr(0,checksum_pos));
    }
  }

private:
  static uint8_t calculate_checksum(std::string_view sv) {
    return std::accumulate(sv.begin(), sv.end(), 0, [](char a, char b) -> bool { return a ^ b; });
  }
}; // class Sentence Parser

// Takes a stream of bytes and breaks them into NMEA sentences
class StreamParser {
  SentenceParser m_sentence_parser;
  std::string m_buffer;
public:

  void read(char b) {
    m_buffer.push_back(b);
    if ('\n' == m_buffer.back()) {
      m_sentence_parser.read(std::move(m_buffer));
      m_buffer.clear();
    } else if (82 < m_buffer.size()) {
      m_buffer.clear();
    }
  }

}; // class Parser2

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

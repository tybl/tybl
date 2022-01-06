// License: The Unlicense (https://unlicense.org)

#include "doctest/doctest.h"

#include <iostream>
#include <memory>
#include <string>

namespace nmea {

struct Sentence {

  virtual ~Sentence() = default;

  virtual void parse(std::string const&) = 0;

}; // class Sentence

class GGASentence
  : public Sentence
{
public:

  virtual ~GGASentence() = default;

  void parse(std::string const& sentence) override {
    auto comma1 = sentence.find(',');
    auto comma2 = sentence.find(',',comma1);
    auto comma3 = sentence.find(',',comma2);
    std::cout << comma1 << ',' << comma2 << ',' << comma3 << std::endl;
  }

}; // class GGASentence

std::unique_ptr<Sentence> parse(std::string const& input)
{
  auto it = input.begin();
  if ('$' != *it++) { std::cerr << __LINE__ << std::endl; return nullptr; }
  if ('G' != *it++) { std::cerr << __LINE__ << std::endl; return nullptr; }
  // GL, GN, GP
  if ('L' != *it && 'N' != *it && 'P' != *it) {
    std::cerr << __LINE__ << std::endl;
    return nullptr;
  }
  ++it;
  if ('G' == *it) {
    ++it;
    if ('G' == it[0] && 'A' == it[1]) {
      // GGA
      std::cerr << __LINE__ << std::endl;
    } else if ('S' == *it) {
      ++it;
      if ('A' == *it) {
        // GSA
        std::cerr << __LINE__ << std::endl;
      } else if ('V' == *it) {
        // GSV
        std::cerr << __LINE__ << std::endl;
      }
    }
  } else if ('R' == it[0] && 'M' == it[1] && 'C' == it[2]) {
    // RMC
    std::cerr << __LINE__ << std::endl;
  } else if ('V' == it[0] && 'T' == it[1] && 'G' == it[2]) {
    // VTG
    std::cerr << __LINE__ << std::endl;
  }
  return std::make_unique<GGASentence>();
}

} // namespace nmea

TEST_CASE("NMEA GGA Sentence 1") {
  CHECK(nullptr == nmea::parse(""));
  CHECK(nullptr == nmea::parse("GPGGA,00.5"));
  CHECK(nullptr == nmea::parse("$CDACK"));
  std::string gga_input("$GPGGA,064951.000,2307.1256,N,12016.4438,E,1,8,0.95,39.9,M,17.8,M,,*65\r\n");
  nmea::parse(gga_input);
  std::string gsa_input("$GPGSA,A,3,29,21,26,15,18,09,06,10,,,,,2.32,0.95,2.11*00");
  nmea::parse(gsa_input);
  std::string gsv_input("$GPGSV,3,1,09,29,36,029,42,21,46,314,43,26,44,020,43,15,21,321,39*7D");
  nmea::parse(gsv_input);
  std::string rmc_input("$GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406,3.05,W,A*2C");
  nmea::parse(rmc_input);
  std::string vtg_input("$GPVTG,165.48,T,,M,0.03,N,0.06,K,A*37");
  nmea::parse(vtg_input);
}

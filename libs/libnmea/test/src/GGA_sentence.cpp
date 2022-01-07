// License: The Unlicense (https://unlicense.org)

#include "doctest/doctest.h"

#include <iostream>
#include <memory>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <iomanip>

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

std::unique_ptr<Sentence> parse_gga(std::istream& in) {
  std::string value;
  if (!std::getline(in,value,',')) {
    throw std::runtime_error("Error: Failed to get NMEA GGA UTC time");
  }
  std::cerr << __LINE__ << ": UTC Time: " << value;
  while (std::getline(in,value,',')) {
    std::cerr << __LINE__ << ": " << value << std::endl;
  }
  return nullptr;
}

std::unique_ptr<Sentence> parse_nmea(std::istream& in) {
  std::string value;
  if (std::getline(in, value, ',')) {
    if ("$GPGGA" == value) { return parse_gga(in); }
  }
}


std::unique_ptr<Sentence> parse_gga(std::string_view input) {
#if 0
  constexpr std::string_view delim{","};
  for (const auto word : std::views::split_view(input, delim))
    std::cerr << __LINE__ << ": "
              << std::quoted(std::string_view(word.begin(), word.end()))
              << std::endl;
#endif
  std::cerr << __LINE__ << std::endl;
  return nullptr;
}

std::unique_ptr<Sentence> parse(std::string_view input) {
  if (input.empty()) { std::cerr << __LINE__ << std::endl; return nullptr; }
  if (input.starts_with("$GPGGA,") || input.starts_with("$GLGGA")) { return parse_gga(input.substr(7)); }
  if (input.starts_with("$GPGSA,") || input.starts_with("$GLGSA")) { std::cerr << __LINE__ << std::endl; return nullptr; }
  if (input.starts_with("$GPGSV,") || input.starts_with("$GLGSV")) { std::cerr << __LINE__ << std::endl; return nullptr; }
  if (input.starts_with("$GPRMC,") || input.starts_with("$GLRMC")) { std::cerr << __LINE__ << std::endl; return nullptr; }
  if (input.starts_with("$GPVTG,") || input.starts_with("$GLVTG")) { std::cerr << __LINE__ << std::endl; return nullptr; }
  std::cerr << __LINE__ << std::endl;
  return nullptr;
}

} // namespace nmea

TEST_CASE("NMEA GGA Sentence 1") {
  CHECK(nullptr == nmea::parse(""));
  CHECK(nullptr == nmea::parse("GPGGA,00.5"));
  CHECK(nullptr == nmea::parse("$CDACK"));
  std::istringstream gga_input("$GPGGA,064951.000,2307.1256,N,12016.4438,E,1,8,0.95,39.9,M,17.8,M,,*65\r\n");
  nmea::parse_nmea(gga_input);
  std::string gsa_input("$GPGSA,A,3,29,21,26,15,18,09,06,10,,,,,2.32,0.95,2.11*00");
  nmea::parse(gsa_input);
  std::string gsv_input("$GPGSV,3,1,09,29,36,029,42,21,46,314,43,26,44,020,43,15,21,321,39*7D");
  nmea::parse(gsv_input);
  std::string rmc_input("$GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406,3.05,W,A*2C");
  nmea::parse(rmc_input);
  std::string vtg_input("$GPVTG,165.48,T,,M,0.03,N,0.06,K,A*37");
  nmea::parse(vtg_input);
}

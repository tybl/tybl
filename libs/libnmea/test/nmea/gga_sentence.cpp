// License: The Unlicense (https://unlicense.org)

#include <vodka/parse_error.hpp>

#include <doctest/doctest.h>
#include <spdlog/spdlog.h>

#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>

namespace nmea {

struct sentence {

  virtual ~sentence() = default;

  virtual void parse(std::string const&) = 0;

}; // class sentence

class gga_sentence : public sentence {
public:
  ~gga_sentence() override = default;

  void parse(std::string const& p_s) override {
    auto comma1 = p_s.find(',');
    auto comma2 = p_s.find(',', comma1);
    auto comma3 = p_s.find(',', comma2);
    spdlog::info("{},{},{}\n", comma1, comma2, comma3);
  }

}; // class gga_sentence

auto parse_gga(std::istream& p_in) -> std::unique_ptr<sentence> {
  std::string value;
  if (!std::getline(p_in, value, ',')) {
    throw tybl::vodka::parse_error("Error: Failed to get NMEA GGA UTC time");
  }
  std::cerr << __LINE__ << ": UTC Time: " << value << std::endl;
  if (!std::getline(p_in, value, ',')) {
    throw tybl::vodka::parse_error("Error: Failed to get NMEA GGA latitude value");
  }
  std::cerr << __LINE__ << ": Latitude: " << value << std::endl;
  if (!std::getline(p_in, value, ',')) {
    throw tybl::vodka::parse_error("Error: Failed to get NMEA GGA N/S Indicator");
  }
  std::cerr << __LINE__ << ": N/S Indicator: " << value << std::endl;
  if (!std::getline(p_in, value, ',')) {
    throw tybl::vodka::parse_error("Error: Failed to get NMEA GGA Longitude");
  }
  std::cerr << __LINE__ << ": Longitude: " << value << std::endl;
  if (!std::getline(p_in, value, ',')) {
    throw tybl::vodka::parse_error("Error: Failed to get NMEA GGA E/W Indicator");
  }
  std::cerr << __LINE__ << ": E/W Indicator: " << value << std::endl;
  if (!std::getline(p_in, value, ',')) {
    throw tybl::vodka::parse_error("Error: Failed to get NMEA GGA Position Indicator");
  }
  std::cerr << __LINE__ << ": Position Indicator: " << value << std::endl;
  if (!std::getline(p_in, value, ',')) {
    throw tybl::vodka::parse_error("Error: Failed to get NMEA GGA Satellites Used");
  }
  std::cerr << __LINE__ << ": Satellites Used: " << value << std::endl;
  if (!std::getline(p_in, value, ',')) {
    throw tybl::vodka::parse_error("Error: Failed to get NMEA GGA Horizontal Dilution of Precision");
  }
  std::cerr << __LINE__ << ": Horizontal Dilution of Precision: " << value << std::endl;
  if (!std::getline(p_in, value, ',')) {
    throw tybl::vodka::parse_error("Error: Failed to get NMEA GGA MSL Altitude");
  }
  std::cerr << __LINE__ << ": MSL Altitude: " << value << std::endl;
  while (std::getline(p_in, value, ',')) {
    std::cerr << __LINE__ << ": " << value << std::endl;
  }
  return nullptr;
}

auto parse_nmea(std::istream& p_in) -> std::unique_ptr<sentence> {
  if (std::string value; std::getline(p_in, value, ',')) {
    if ("$GPGGA" == value) {
      return parse_gga(p_in);
    }
  }
  return nullptr;
}

auto parse_gga(std::string_view /*input*/) -> std::unique_ptr<sentence> {
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

auto parse(std::string_view p_input) -> std::unique_ptr<sentence> {
  if (p_input.empty()) {
    std::cerr << __LINE__ << std::endl;
    return nullptr;
  }
  if (p_input.starts_with("$GPGGA,") || p_input.starts_with("$GLGGA")) {
    return parse_gga(p_input.substr(7));
  }
  if (p_input.starts_with("$GPGSA,") || p_input.starts_with("$GLGSA")) {
    std::cerr << __LINE__ << std::endl;
    return nullptr;
  }
  if (p_input.starts_with("$GPGSV,") || p_input.starts_with("$GLGSV")) {
    std::cerr << __LINE__ << std::endl;
    return nullptr;
  }
  if (p_input.starts_with("$GPRMC,") || p_input.starts_with("$GLRMC")) {
    std::cerr << __LINE__ << std::endl;
    return nullptr;
  }
  if (p_input.starts_with("$GPVTG,") || p_input.starts_with("$GLVTG")) {
    std::cerr << __LINE__ << std::endl;
    return nullptr;
  }
  std::cerr << __LINE__ << std::endl;
  return nullptr;
}

} // namespace nmea

TEST_CASE("NMEA GGA sentence 1") {
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

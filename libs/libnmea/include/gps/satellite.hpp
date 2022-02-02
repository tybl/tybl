// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_GPS_SATELLITE_HPP
#define TYBL_NMEA_GPS_SATELLITE_HPP

#include <cstdint>
#include <string>

namespace gps {

struct satellite {
  double snr;       // 0-99 dB
  uint32_t prn;     // id - 0-32
  double elevation; // 0-90 deg
  double azimuth;   // 0-359 deg

  satellite();

  auto to_string() -> std::string;

  operator std::string();

}; // struct satellite

} // namespace gps

#endif // TYBL_NMEA_GPS_SATELLITE_HPP

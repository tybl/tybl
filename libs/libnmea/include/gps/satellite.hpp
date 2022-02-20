// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_GPS_SATELLITE_HPP
#define TYBL_NMEA_GPS_SATELLITE_HPP

#include <cstdint>
#include <string>

namespace tybl::nmea::gps {

struct satellite {
  double snr;       // 0-99 dB
  uint32_t prn;     // id - 0-32
  double elevation; // 0-90 deg
  double azimuth;   // 0-359 deg

  [[nodiscard]] auto to_string() const -> std::string;

  explicit operator std::string() const;

}; // struct satellite

} // namespace tybl::nmea::gps

#endif // TYBL_NMEA_GPS_SATELLITE_HPP
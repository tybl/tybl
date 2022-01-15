// License: The Unlicense (https://unlicense.org)
#pragma once

#include <cstdint>
#include <string>

namespace gps {

struct satellite {
  //satellite data
  double snr;      // 0-99 dB
  uint32_t prn;    // id - 0-32
  double elevation;  // 0-90 deg
  double azimuth;    // 0-359 deg
public:
  satellite();

  std::string to_string();

  operator std::string();

}; // struct satellite

} // namespace gps

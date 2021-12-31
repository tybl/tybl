#pragma once

#include <cstdint>
#include <string>

namespace gps {

struct Satellite {
  //satellite data
  double snr;      // 0-99 dB
  uint32_t prn;    // id - 0-32
  double elevation;  // 0-90 deg
  double azimuth;    // 0-359 deg
public:

  Satellite();

  std::string to_string();

  operator std::string();

}; // struct Satellite

} // namespace gps

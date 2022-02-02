// License: The Unlicense (https://unlicense.org)
#include "gps/satellite.hpp"

#include <iomanip>
#include <sstream>

namespace gps {

satellite::satellite()
  : snr(0)
  , prn(0)
  , elevation(0)
  , azimuth(0) {}

auto satellite::to_string() const -> std::string {
  std::stringstream ss;

  ss << "[PRN: " << std::setw(3) << std::setfill(' ') << prn << " "
     << "  SNR: " << std::setw(3) << std::setfill(' ') << snr << " dB  "
     << "  Azimuth: " << std::setw(3) << std::setfill(' ') << azimuth << " deg "
     << "  Elevation: " << std::setw(3) << std::setfill(' ') << elevation << " deg  "
     << "]";

  return ss.str();
}

satellite::operator std::string() { return to_string(); }

} // namespace gps

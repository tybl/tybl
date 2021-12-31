#include "gps/Satellite.hpp"

#include <iomanip>
#include <sstream>

namespace gps {

Satellite::Satellite()
  : snr(0)
  , prn(0)
  , elevation(0)
  , azimuth(0)
{}

std::string Satellite::toString() {
  std::stringstream ss;

  ss << "[PRN: " << std::setw(3) << std::setfill(' ') << prn << " "
    << "  SNR: " << std::setw(3) << std::setfill(' ') << snr << " dB  "
    << "  Azimuth: " << std::setw(3) << std::setfill(' ') << azimuth << " deg "
    << "  Elevation: " << std::setw(3) << std::setfill(' ') << elevation << " deg  "
    << "]";

  return ss.str();
}

Satellite::operator std::string() {
  return toString();
}

} // namespace gps

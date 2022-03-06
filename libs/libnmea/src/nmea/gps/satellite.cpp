// License: The Unlicense (https://unlicense.org)
#include <nmea/gps/satellite.hpp>

#include <fmt/core.h>

namespace tybl::nmea::gps {

auto satellite::to_string() const -> std::string {
  return fmt::format("[PRN: {} SNR: {} dB, Azimuth: {} deg, Elevation: {} deg ]", prn, snr, azimuth, elevation);
}

satellite::operator std::string() const { return to_string(); }

} // namespace tybl::nmea::gps
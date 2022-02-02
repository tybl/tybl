// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_GPS_ALMANAC_HPP
#define TYBL_NMEA_GPS_ALMANAC_HPP

#include "gps/satellite.hpp"

#include <cstdint>
#include <vector>

namespace nmea {
class GPSService;
} // namespace nmea

namespace gps {

class almanac {
  friend nmea::GPSService;
  uint32_t m_visible_size;
  uint32_t m_total_pages = 0;
  uint32_t m_processed_pages = 0;
  void clear(); // will remove all information from the satellites
  void update_satellite(gps::satellite const& p_sat);

public:
  // mapped by prn
  std::vector<gps::satellite> satellites;
  [[nodiscard]] auto average_snr() const -> double;
  [[nodiscard]] auto min_snr() const -> double;
  [[nodiscard]] auto max_snr() const -> double;
  [[nodiscard]] auto percent_complete() const -> double;

}; // class almanac

} // namespace gps

#endif // TYBL_NMEA_GPS_ALMANAC_HPP

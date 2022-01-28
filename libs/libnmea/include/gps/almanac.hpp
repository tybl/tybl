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
  uint32_t m_total_pages;
  uint32_t m_processed_pages;
  void clear(); // will remove all information from the satellites
  void update_satellite(gps::satellite const& p_sat);

public:
  almanac();

  // mapped by prn
  std::vector<gps::satellite> satellites;
  double average_snr() const;
  double min_snr() const;
  double max_snr() const;
  double percent_complete() const;

}; // class almanac

} // namespace gps

#endif // TYBL_NMEA_GPS_ALMANAC_HPP

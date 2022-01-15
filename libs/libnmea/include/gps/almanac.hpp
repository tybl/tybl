#pragma once

#include "gps/satellite.hpp"

#include <cstdint>
#include <vector>

namespace nmea {
  class GPSService;
} // namespace nmea

namespace gps {

class almanac {
  friend nmea::GPSService;
private:
  uint32_t m_visible_size;
  uint32_t m_total_pages;
  uint32_t m_processed_pages;
  void clear();      //will remove all information from the satellites
  void update_satellite(gps::satellite sat);
public:
  almanac();

  //mapped by prn
  std::vector<gps::satellite> satellites;
  double average_snr();
  double min_snr();
  double max_snr();
  double percent_complete();

}; // class almanac

} // namespace gps

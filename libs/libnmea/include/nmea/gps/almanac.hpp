// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_GPS_ALMANAC_HPP
#define TYBL_NMEA_GPS_ALMANAC_HPP

#include <nmea/gps/satellite.hpp>

#include <cstdint>
#include <vector>

namespace tybl::nmea {

class gps_service;

namespace gps {

class almanac {
  friend nmea::gps_service;

  uint32_t m_visible_size{};
  uint32_t m_total_pages = 0;
  uint32_t m_processed_pages = 0;
  void clear(); // will remove all information from the satellites
  void update_satellite(tybl::nmea::gps::satellite const& p_sat);

public:
  // mapped by prn
  std::vector<tybl::nmea::gps::satellite> satellites;
  [[nodiscard, gnu::pure]] auto average_snr() const -> double;
  [[nodiscard, gnu::pure]] auto min_snr() const -> double;
  [[nodiscard, gnu::pure]] auto max_snr() const -> double;
  [[nodiscard, gnu::pure]] auto percent_complete() const -> double;

}; // class almanac

} // namespace gps

} // namespace tybl::nmea

#endif // TYBL_NMEA_GPS_ALMANAC_HPP
// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_GPS_FIX_HPP
#define TYBL_NMEA_GPS_FIX_HPP

#include "gps/almanac.hpp"
#include "gps/satellite.hpp"
#include "gps/timestamp.hpp"

#include <chrono>
#include <cstdint>
#include <string>

namespace nmea {
class GPSService;
} // namespace nmea

namespace gps {

class fix {
  friend nmea::GPSService;
  bool m_has_lock;
  auto set_lock(bool p_b) -> bool; // returns true if lock status **changed***, false otherwise.

public:
  fix();
  virtual ~fix();

  gps::almanac almanac;
  gps::timestamp timestamp;

  char status;     // Status: A=active, V=void (not locked)
  uint8_t type;    // Type: 1=none, 2=2d, 3=3d
  uint8_t quality; // Quality:
                   //    0 = invalid
                   //    1 = GPS fix (SPS)
                   //    2 = DGPS fix
                   //    3 = PPS fix
                   //    4 = Real Time Kinematic (RTK)
                   //    5 = Float RTK
                   //    6 = estimated (dead reckoning) (2.3 feature)

  double dilution;            // Combination of Vertical & Horizontal
  double horizontal_dilution; // Horizontal dilution of precision, initialized to 100, best =1, worst = >20
  double vertical_dilution;   // Vertical is less accurate

  double altitude;     // meters
  double latitude;     // degrees N
  double longitude;    // degrees E
  double speed;        // km/h
  double travel_angle; // degrees true north (0-360)
  int32_t tracking_satellites;
  int32_t visible_satellites;

  auto locked() const -> bool;
  auto horizontal_accuracy() const -> double;
  auto vertical_accuracy() const -> double;
  auto has_estimate() const -> bool;

  auto time_since_last_update() const
      -> std::chrono::seconds; // Return seconds difference from last timestamp and right now.

  auto to_string() -> std::string;
  operator std::string();

  static auto ordinal_direction(double p_deg, bool p_abbrev = false) -> std::string;
}; // class fix

} // namespace gps

#endif // TYBL_NMEA_GPS_FIX_HPP

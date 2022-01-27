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
  bool set_lock(bool p_b); // returns true if lock status **changed***, false otherwise.

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

  bool locked();
  double horizontal_accuracy();
  double vertical_accuracy();
  bool has_estimate();

  std::chrono::seconds time_since_last_update(); // Return seconds difference from last timestamp and right now.

  std::string to_string();
  operator std::string();

  static std::string ordinal_direction(double p_deg, bool p_abbrev = false);
}; // class fix

} // namespace gps

#endif // TYBL_NMEA_GPS_FIX_HPP

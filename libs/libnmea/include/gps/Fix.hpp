#pragma once

#include "gps/Almanac.hpp"
#include "gps/Satellite.hpp"
#include "gps/Timestamp.hpp"

#include <chrono>
#include <cstdint>
#include <string>

namespace nmea {
  class GPSService;
} // namespace nmea

namespace gps {

class Fix {
  friend nmea::GPSService;

private:

  bool m_haslock;
  bool setlock(bool b);    //returns true if lock status **changed***, false otherwise.

public:

  Fix();
  virtual ~Fix();

  gps::Almanac almanac;
  gps::Timestamp timestamp;

  char status;    // Status: A=active, V=void (not locked)
  uint8_t type;    // Type: 1=none, 2=2d, 3=3d
  uint8_t quality;  // Quality: 
            //    0 = invalid
            //    1 = GPS fix (SPS)
            //    2 = DGPS fix
            //    3 = PPS fix
            //    4 = Real Time Kinematic (RTK)
            //    5 = Float RTK
            //    6 = estimated (dead reckoning) (2.3 feature)

  double dilution;          // Combination of Vertical & Horizontal
  double horizontalDilution;      // Horizontal dilution of precision, initialized to 100, best =1, worst = >20
  double verticalDilution;      // Vertical is less accurate

  double altitude;    // meters
  double latitude;    // degrees N
  double longitude;    // degrees E
  double speed;      // km/h
  double travelAngle;    // degrees true north (0-360)
  int32_t trackingSatellites;
  int32_t visibleSatellites;

  bool locked();
  double horizontalAccuracy();
  double verticalAccuracy();
  bool hasEstimate();

  std::chrono::seconds timeSinceLastUpdate();  // Returns seconds difference from last timestamp and right now.

  std::string toString();
  operator std::string();

  static std::string travelAngleToCompassDirection(double deg, bool abbrev = false);
}; // class Fix

} // namespace nmea

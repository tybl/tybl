// License: The Unlicense (https://unlicense.org)
#pragma once

#include <units.h>

namespace vodka::coord {

class ecef_t;

class lla_t {
  units::angle::radian_t mLatitude; 
  units::angle::radian_t mLongitude;
  units::length::meter_t mAltitude;
public:

  auto to_ecef() const -> ecef_t;

  auto latitude() const -> units::angle::radian_t;

  auto longitude() const -> units::angle::radian_t;

  auto altitude() const -> units::length::meter_t;

}; // class lla_c

} // namespace vodka::coord

// License: The Unlicense (https://unlicense.org)
#pragma once

#include <units.h>

namespace vodka::coord {

class frd_t;

class rae_t {
  units::length::meter_t mRange;
  units::angle::radian_t mAzimuth;
  units::angle::radian_t mElevation;
public:

  rae_t(units::length::meter_t const& r,
        units::angle::radian_t const& a,
        units::angle::radian_t const& e);

  auto to_frd() const -> frd_t;

  auto range() const -> units::length::meter_t;

  auto azimuth() const -> units::angle::radian_t;

  auto elevation() const -> units::angle::radian_t;

}; // class rae_t

} // namespace vodka::coord

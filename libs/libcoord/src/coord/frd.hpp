// License: The Unlicense (https://unlicense.org)
#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <units.h>

namespace vodka::coord {

class ecef_t;

class frd_t {
  Eigen::Vector3d frd;
public:

  frd_t(units::length::meter_t const& f,
        units::length::meter_t const& r,
        units::length::meter_t const& d);

  auto to_ecef(ecef_t const& ref_pos, Eigen::Quaterniond const& ref_rot) const -> ecef_t;

  auto x() const -> units::length::meter_t;

  auto y() const -> units::length::meter_t;

  auto z() const -> units::length::meter_t;

  auto f() const -> units::length::meter_t;

  auto r() const -> units::length::meter_t;

  auto d() const -> units::length::meter_t;

}; // class frd_t

} // namespace vodka::coord

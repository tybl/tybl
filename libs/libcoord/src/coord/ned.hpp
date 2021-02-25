// License: The Unlicense (https://unlicense.org)
#pragma once

#include <Eigen/Core>
#include <units.h>

namespace vodka::coord {

class ecef_t;

class ned_t {
  Eigen::Vector3d ned;
public:

  auto to_ecef(ecef_t const& ref_pos) const -> ecef_t;

  auto x() const -> units::length::meter_t;

  auto y() const -> units::length::meter_t;

  auto z() const -> units::length::meter_t;

  auto n() const -> units::length::meter_t;

  auto e() const -> units::length::meter_t;

  auto d() const -> units::length::meter_t;

}; // class ned_t

} // namespace vodka::coord

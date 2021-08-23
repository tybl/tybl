// License: The Unlicense (https://unlicense.org)
#pragma once

#include <Eigen/Core>
#include <units.h>

namespace vodka::coord {

class lla_t;

class ecef_t {
  Eigen::Vector3d ecef;
public:

  using vec = Eigen::Matrix<units::length::meter_t, 3, 1>;

  explicit ecef_t(Eigen::Vector3d pos);

  operator Eigen::Vector3d() const;

  auto to_lla() const -> lla_t;

  auto x() const -> units::length::meter_t;

  auto y() const -> units::length::meter_t;

  auto z() const -> units::length::meter_t;

}; // class ecef_t

} // namespace vodka::coord

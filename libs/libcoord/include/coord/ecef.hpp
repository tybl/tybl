// License: The Unlicense (https://unlicense.org)
#pragma once

#include <Eigen/Core>

namespace vodka::coord {

class lla_t;

class ecef_t {
  Eigen::Vector3d ecef;
public:

  explicit ecef_t(Eigen::Vector3d pos);

  operator Eigen::Vector3d() const;

  auto to_lla() const -> lla_t;

  auto x() const -> double;

  auto y() const -> double;

  auto z() const -> double;

}; // class ecef_t

} // namespace vodka::coord

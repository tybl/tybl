// License: The Unlicense (https://unlicense.org)
#pragma once

#include <Eigen/Core>

namespace vodka::coord {

class ecef_t;

class enu_t {
  Eigen::Vector3d enu;
public:

  auto to_ecef(ecef_t const& ref_pos) const -> ecef_t;

  auto x() const -> double;

  auto y() const -> double;

  auto z() const -> double;

  auto e() const -> double;

  auto n() const -> double;

  auto u() const -> double;

}; // class enu_t

} // namespace vodka::coord

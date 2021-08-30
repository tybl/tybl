// License: The Unlicense (https://unlicense.org)
#pragma once

#include <Eigen/Core>

namespace vodka::coord {

class ecef_t;

class ned_t {
  Eigen::Vector3d ned;
public:

  auto to_ecef(ecef_t const& ref_pos) const -> ecef_t;

  auto x() const -> double;

  auto y() const -> double;

  auto z() const -> double;

  auto n() const -> double;

  auto e() const -> double;

  auto d() const -> double;

}; // class ned_t

} // namespace vodka::coord

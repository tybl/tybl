// License: The Unlicense (https://unlicense.org)
#include "coord/ecef.hpp"

#include "coord/lla.hpp"

namespace vodka::coord {

ecef_t::ecef_t(Eigen::Vector3d pos)
  : ecef(std::move(pos)) { }

ecef_t::operator Eigen::Vector3d() const {
  return ecef;
}

auto ecef_t::to_lla() const -> lla_t {
  // TODO(tybl): Implement this function
  static_cast<void>(this);
  throw std::runtime_error(__func__);
}

auto ecef_t::x() const -> double {
  return ecef[0];
}

auto ecef_t::y() const -> double {
  return ecef[1];
}

auto ecef_t::z() const -> double {
  return ecef[2];
}

} // namespace vodka::coord

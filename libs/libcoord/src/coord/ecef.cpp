// License: The Unlicense (https://unlicense.org)
#include "ecef.hpp"

#include "lla.hpp"

namespace vodka::coord {

ecef_t::ecef_t(Eigen::Vector3d pos)
  : ecef(std::move(pos)) { }

ecef_t::operator Eigen::Vector3d() const {
  return ecef;
}

auto ecef_t::to_lla() const -> lla_t {
  // TODO(tlyons): Implement this function
  static_cast<void>(this);
  throw std::runtime_error(__func__);
}

auto ecef_t::x() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(ecef[0]);
}

auto ecef_t::y() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(ecef[1]);
}

auto ecef_t::z() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(ecef[2]);
}

} // namespace vodka::coord

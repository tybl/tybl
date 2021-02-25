// License: The Unlicense (https://unlicense.org)
#include "lla.hpp"

#include "ecef.hpp"

namespace vodka::coord {

auto lla_t::to_ecef() const -> ecef_t {
  // TODO(tblyons): Implement this function
  throw std::runtime_error(__func__);
}

auto lla_t::latitude() const -> units::angle::radian_t {
  return mLatitude;
}

auto lla_t::longitude() const -> units::angle::radian_t {
  return mLongitude;
}

auto lla_t::altitude() const -> units::length::meter_t {
  return mAltitude;
}

} // namespace vodka::coord

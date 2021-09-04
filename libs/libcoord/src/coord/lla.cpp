// License: The Unlicense (https://unlicense.org)
#include "coord/lla.hpp"

#include "coord/ecef.hpp"

#include <stdexcept>

namespace vodka::coord {

auto lla_t::to_ecef() const -> ecef_t {
  // TODO(tybl): Implement this function
  throw std::runtime_error(__func__);
}

auto lla_t::latitude() const -> double {
  return mLatitude;
}

auto lla_t::longitude() const -> double {
  return mLongitude;
}

auto lla_t::altitude() const -> double {
  return mAltitude;
}

} // namespace vodka::coord

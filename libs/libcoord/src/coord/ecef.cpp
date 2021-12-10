// License: The Unlicense (https://unlicense.org)
#include "coord/ecef.hpp"

#include "coord/lla.hpp"
#include "vodka/utility/move.hpp"

#include <stdexcept>

namespace tybl::coord {

ecef_t::ecef_t(lynel::cvec3<double> pos)
  : ecef(vodka::move(pos)) { }

ecef_t::operator lynel::cvec3<double>() const {
  return ecef;
}

auto ecef_t::to_lla() const -> lla_t {
  // TODO(tybl): Implement this function
  static_cast<void>(this);
  throw std::runtime_error(__func__); // NOLINT
}

auto ecef_t::x() const -> double {
  return ecef.x;
}

auto ecef_t::y() const -> double {
  return ecef.y;
}

auto ecef_t::z() const -> double {
  return ecef.z;
}

} // namespace tybl::coord

// License: The Unlicense (https://unlicense.org)
#include "coord/ecef.hpp"

#include "coord/lla.hpp"
#include "vodka/utility/move.hpp"

#include <stdexcept>

namespace tybl::coord {

ecef_t::ecef_t(lynel::cvec3<double> pos)
  : m_ecef(vodka::move(pos)) { }

ecef_t::operator lynel::cvec3<double>() const {
  return m_ecef;
}

auto ecef_t::to_lla() const -> lla_t {
  // TODO(tybl): Implement this function
  static_cast<void>(this);
  throw std::runtime_error(__func__); // NOLINT
}

auto ecef_t::x() const -> double {
  return m_ecef.x;
}

auto ecef_t::y() const -> double {
  return m_ecef.y;
}

auto ecef_t::z() const -> double {
  return m_ecef.z;
}

} // namespace tybl::coord

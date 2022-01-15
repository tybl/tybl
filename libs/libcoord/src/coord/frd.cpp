// License: The Unlicense (https://unlicense.org)
#include "coord/frd.hpp"

#include "coord/ecef.hpp"

namespace tybl::coord {

frd_t::frd_t(double f, double r, double d)
  : m_frd({f, r, d}) { }

auto frd_t::to_ecef(ecef_t const& ref_pos, lynel::quaternion const& /*ref_rot*/) const -> ecef_t {
  static_cast<void>(this);
  // TODO(tybl)
  //return ecef_t(ref_rot * frd + static_cast<lynel::vec3d>(ref_pos));
  return ref_pos;
}

auto frd_t::x() const -> double {
  return m_frd.x;
}

auto frd_t::y() const -> double {
  return m_frd.y;
}

auto frd_t::z() const -> double {
  return m_frd.z;
}

auto frd_t::f() const -> double {
  return m_frd.x;
}

auto frd_t::r() const -> double {
  return m_frd.y;
}

auto frd_t::d() const -> double {
  return m_frd.z;
}

} // namespace tybl::coord

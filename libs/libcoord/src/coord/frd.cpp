// License: The Unlicense (https://unlicense.org)
#include "coord/frd.hpp"

#include "coord/ecef.hpp"

namespace tybl::coord {

frd_t::frd_t(double f, double r, double d)
  : frd({f, r, d}) { }

auto frd_t::to_ecef(ecef_t const& ref_pos, linal::quaternion const& /*ref_rot*/) const -> ecef_t {
  // TODO(tybl)
  //return ecef_t(ref_rot * frd + static_cast<linal::vec3d>(ref_pos));
  return ref_pos;
}

auto frd_t::x() const -> double {
  return frd.x;
}

auto frd_t::y() const -> double {
  return frd.y;
}

auto frd_t::z() const -> double {
  return frd.z;
}

auto frd_t::f() const -> double {
  return frd.x;
}

auto frd_t::r() const -> double {
  return frd.y;
}

auto frd_t::d() const -> double {
  return frd.z;
}

} // namespace tybl::coord

// License: The Unlicense (https://unlicense.org)
#include "coord/frd.hpp"

#include "coord/ecef.hpp"

#include <Eigen/Geometry>

namespace vodka::coord {

frd_t::frd_t(double f, double r, double d)
  : frd(f, r, d) { }

auto frd_t::to_ecef(ecef_t const& ref_pos, Eigen::Quaterniond const& ref_rot) const -> ecef_t {
  return ecef_t(ref_rot * frd + static_cast<Eigen::Vector3d>(ref_pos));
}

auto frd_t::x() const -> double {
  return frd[0];
}

auto frd_t::y() const -> double {
  return frd[1];
}

auto frd_t::z() const -> double {
  return frd[2];
}

auto frd_t::f() const -> double {
  return frd[0];
}

auto frd_t::r() const -> double {
  return frd[1];
}

auto frd_t::d() const -> double {
  return frd[2];
}

} // namespace vodka::coord

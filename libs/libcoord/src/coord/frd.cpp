// License: The Unlicense (https://unlicense.org)
#include "frd.hpp"

#include "ecef.hpp"

#include <Eigen/Geometry>

namespace vodka::coord {

frd_t::frd_t(units::length::meter_t const& f,
             units::length::meter_t const& r,
             units::length::meter_t const& d)
  : frd(f.to<double>(), r.to<double>(), d.to<double>()) { }

auto frd_t::to_ecef(ecef_t const& ref_pos, Eigen::Quaterniond const& ref_rot) const -> ecef_t {
  return ecef_t(ref_rot * frd + static_cast<Eigen::Vector3d>(ref_pos));
}

auto frd_t::x() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(frd[0]);
}

auto frd_t::y() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(frd[1]);
}

auto frd_t::z() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(frd[2]);
}

auto frd_t::f() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(frd[0]);
}

auto frd_t::r() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(frd[1]);
}

auto frd_t::d() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(frd[2]);
}

} // namespace vodka::coord

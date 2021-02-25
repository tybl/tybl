// License: The Unlicense (https://unlicense.org)
#include "enu.hpp"

#include "ecef.hpp"

namespace vodka::coord {

auto enu_t::to_ecef(ecef_t const& ref_pos) const -> ecef_t {
  return ref_pos;
}

auto enu_t::x() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(enu[0]);
}

auto enu_t::y() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(enu[1]);
}

auto enu_t::z() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(enu[2]);
}

auto enu_t::e() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(enu[0]);
}

auto enu_t::n() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(enu[1]);
}

auto enu_t::u() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(enu[2]);
}

} // namespace vodka::coord

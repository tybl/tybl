// License: The Unlicense (https://unlicense.org)
#include "ned.hpp"

#include "ecef.hpp"

namespace vodka::coord {

auto ned_t::to_ecef(ecef_t const& ref_pos) const -> ecef_t {
  return ref_pos;
}

auto ned_t::x() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(ned[0]);
}

auto ned_t::y() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(ned[1]);
}

auto ned_t::z() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(ned[2]);
}

auto ned_t::n() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(ned[0]);
}

auto ned_t::e() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(ned[1]);
}

auto ned_t::d() const -> units::length::meter_t {
  return static_cast<units::length::meter_t>(ned[2]);
}

} // namespace vodka::coord

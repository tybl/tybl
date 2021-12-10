// License: The Unlicense (https://unlicense.org)
#include "coord/enu.hpp"

#include "coord/ecef.hpp"

namespace tybl::coord {

auto enu_t::to_ecef(ecef_t const& ref_pos) const -> ecef_t {
  static_cast<void>(this);
  return ref_pos;
}

auto enu_t::x() const -> double {
  return enu.x;
}

auto enu_t::y() const -> double {
  return enu.y;
}

auto enu_t::z() const -> double {
  return enu.z;
}

auto enu_t::e() const -> double {
  return enu.x;
}

auto enu_t::n() const -> double {
  return enu.y;
}

auto enu_t::u() const -> double {
  return enu.z;
}

} // namespace tybl::coord

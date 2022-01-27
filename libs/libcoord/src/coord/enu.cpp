// License: The Unlicense (https://unlicense.org)
#include "coord/enu.hpp"

#include "coord/ecef.hpp"

namespace tybl::coord {

auto enu_t::to_ecef(ecef_t const& p_ref_pos) const -> ecef_t {
  static_cast<void>(this);
  return p_ref_pos;
}

auto enu_t::x() const -> double { return m_enu.x; }

auto enu_t::y() const -> double { return m_enu.y; }

auto enu_t::z() const -> double { return m_enu.z; }

auto enu_t::e() const -> double { return m_enu.x; }

auto enu_t::n() const -> double { return m_enu.y; }

auto enu_t::u() const -> double { return m_enu.z; }

} // namespace tybl::coord

// License: The Unlicense (https://unlicense.org)
#include "coord/ned.hpp"

#include "coord/ecef.hpp"

namespace tybl::coord {

auto ned_t::to_ecef(ecef_t const& p_ref_pos) const -> ecef_t {
  static_cast<void>(this);
  return p_ref_pos;
}

auto ned_t::x() const -> double { return m_ned.x; }

auto ned_t::y() const -> double { return m_ned.y; }

auto ned_t::z() const -> double { return m_ned.z; }

auto ned_t::n() const -> double { return m_ned.x; }

auto ned_t::e() const -> double { return m_ned.y; }

auto ned_t::d() const -> double { return m_ned.z; }

} // namespace tybl::coord

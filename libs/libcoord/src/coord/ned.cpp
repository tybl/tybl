// License: The Unlicense (https://unlicense.org)
#include "coord/ned.hpp"

#include "coord/ecef.hpp"

namespace vodka::coord {

auto ned_t::to_ecef(ecef_t const& ref_pos) const -> ecef_t {
  return ref_pos;
}

auto ned_t::x() const -> double {
  return ned[0];
}

auto ned_t::y() const -> double {
  return ned[1];
}

auto ned_t::z() const -> double {
  return ned[2];
}

auto ned_t::n() const -> double {
  return ned[0];
}

auto ned_t::e() const -> double {
  return ned[1];
}

auto ned_t::d() const -> double {
  return ned[2];
}

} // namespace vodka::coord

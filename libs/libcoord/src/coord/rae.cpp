// License: The Unlicense (https://unlicense.org)
#include "coord/rae.hpp"

#include "coord/frd.hpp"

#include <cmath>

namespace tybl::coord {

rae_t::rae_t(double r, double a, double e)
  : m_range(r)
  , m_azimuth(a)
  , m_elevation(e)
  { }

auto rae_t::to_frd() const -> frd_t {
  const auto hyp = std::cos(m_elevation) * m_range;
  const auto f = std::sin(m_azimuth) * hyp;
  const auto r = std::cos(m_azimuth) * hyp;
  const auto d = std::sin(m_elevation) * m_range;
  return { f, r, d };
}

auto rae_t::range() const -> double {
  return m_range;
}

auto rae_t::azimuth() const -> double {
  return m_azimuth;
}

auto rae_t::elevation() const -> double {
  return m_elevation;
}

} // namespace tybl::coord

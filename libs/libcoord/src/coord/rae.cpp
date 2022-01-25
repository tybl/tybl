// License: The Unlicense (https://unlicense.org)
#include "coord/rae.hpp"

#include "coord/frd.hpp"

#include <cmath> // cos, sin

namespace tybl::coord {

rae_t::rae_t(double p_range, double p_azimuth, double p_elevation)
  : m_range(p_range)
  , m_azimuth(p_azimuth)
  , m_elevation(p_elevation) {}

auto rae_t::to_frd() const -> frd_t {
  const auto hypotenuse = std::cos(elevation()) * range();
  const auto front = std::sin(azimuth()) * hypotenuse;
  const auto right = std::cos(azimuth()) * hypotenuse;
  const auto down = std::sin(elevation()) * range();
  return {front, right, down};
}

auto rae_t::range() const -> double { return m_range; }

auto rae_t::azimuth() const -> double { return m_azimuth; }

auto rae_t::elevation() const -> double { return m_elevation; }

} // namespace tybl::coord

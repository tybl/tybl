// License: The Unlicense (https://unlicense.org)
#include "coord/rae.hpp"

#include "coord/frd.hpp"

namespace vodka::coord {

rae_t::rae_t(double r, double a, double e)
  : mRange(r)
  , mAzimuth(a)
  , mElevation(e)
  { }

auto rae_t::to_frd() const -> frd_t {
  const auto hyp = std::cos(mElevation) * mRange;
  const auto f = std::sin(mAzimuth) * hyp;
  const auto r = std::cos(mAzimuth) * hyp;
  const auto d = std::sin(mElevation) * mRange;
  return frd_t(f, r, d);
}

auto rae_t::range() const -> double {
  return mRange;
}

auto rae_t::azimuth() const -> double {
  return mAzimuth;
}

auto rae_t::elevation() const -> double {
  return mElevation;
}

} // namespace vodka::coord

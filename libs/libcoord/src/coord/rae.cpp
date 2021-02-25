// License: The Unlicense (https://unlicense.org)
#include "rae.hpp"

#include "frd.hpp"

namespace vodka::coord {

rae_t::rae_t(units::length::meter_t const& r,
             units::angle::radian_t const& a,
             units::angle::radian_t const& e)
  : mRange(r)
  , mAzimuth(a)
  , mElevation(e)
  { }

auto rae_t::to_frd() const -> frd_t {
  const auto hyp = units::math::cos(mElevation) * mRange;
  const auto f = units::math::sin(mAzimuth) * hyp;
  const auto r = units::math::cos(mAzimuth) * hyp;
  const auto d = units::math::sin(mElevation) * mRange;
  return frd_t(f, r, d);
}

auto rae_t::range() const -> units::length::meter_t {
  return mRange;
}

auto rae_t::azimuth() const -> units::angle::radian_t {
  return mAzimuth;
}

auto rae_t::elevation() const -> units::angle::radian_t {
  return mElevation;
}

} // namespace vodka::coord

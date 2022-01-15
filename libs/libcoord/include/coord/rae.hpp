// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COORD_RAE_HPP
#define TYBL_COORD_RAE_HPP

namespace tybl::coord {

class frd_t;

class rae_t {
  double mRange;
  double mAzimuth;
  double mElevation;
public:

  rae_t(double r, double a, double e);

  auto to_frd() const -> frd_t;

  auto range() const -> double;

  auto azimuth() const -> double;

  auto elevation() const -> double;

}; // class rae_t

} // namespace tybl::coord

#endif // TYBL_COORD_RAE_HPP
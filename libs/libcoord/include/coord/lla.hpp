// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COORD_LLA_HPP
#define TYBL_COORD_LLA_HPP

namespace tybl::coord {

class ecef_t;

class lla_t {
  double mLatitude;
  double mLongitude;
  double mAltitude;
public:

  auto to_ecef() const -> ecef_t;

  auto latitude() const -> double;

  auto longitude() const -> double;

  auto altitude() const -> double;

}; // class lla_c

} // namespace tybl::coord

#endif // TYBL_COORD_LLA_HPP
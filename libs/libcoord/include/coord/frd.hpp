// License: The Unlicense (https://unlicense.org)
#pragma once

#include "linal/quaternion.hpp"
#include "linal/basic_matrix.hpp"

namespace tybl::coord {

class ecef_t;

class frd_t {
  linal::cvec3<double> frd;
public:

  frd_t(double f, double r, double d);

  auto to_ecef(ecef_t const& ref_pos, linal::quaternion const& ref_rot) const -> ecef_t;

  auto x() const -> double;

  auto y() const -> double;

  auto z() const -> double;

  auto f() const -> double;

  auto r() const -> double;

  auto d() const -> double;

}; // class frd_t

} // namespace tybl::coord

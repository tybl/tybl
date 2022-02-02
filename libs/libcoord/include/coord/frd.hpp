// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COORD_FRD_HPP
#define TYBL_COORD_FRD_HPP

#include "lynel/basic_matrix.hpp"
#include "lynel/quaternion.hpp"

namespace tybl::coord {

class ecef_t;

class frd_t {
  lynel::cvec3<double> m_frd;

public:
  frd_t(double p_f, double p_r, double p_d);

  [[nodiscard,gnu::pure]] auto to_ecef(ecef_t const& p_ref_pos, lynel::quaternion const& p_ref_rot) const -> ecef_t;

  [[nodiscard,gnu::pure]] auto x() const -> double;

  [[nodiscard,gnu::pure]] auto y() const -> double;

  [[nodiscard,gnu::pure]] auto z() const -> double;

  [[nodiscard,gnu::pure]] auto f() const -> double;

  [[nodiscard,gnu::pure]] auto r() const -> double;

  [[nodiscard,gnu::pure]] auto d() const -> double;

}; // class frd_t

} // namespace tybl::coord

#endif // TYBL_COORD_FRD_HPP

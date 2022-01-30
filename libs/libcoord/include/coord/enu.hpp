// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COORD_ENU_HPP
#define TYBL_COORD_ENU_HPP

#include "lynel/basic_matrix.hpp"

namespace tybl::coord {

class ecef_t;

class enu_t {
  lynel::cvec3<double> m_enu;

public:
  [[nodiscard]] auto to_ecef(ecef_t const& p_ref_pos) const -> ecef_t;

  [[nodiscard]] auto x() const -> double;

  [[nodiscard]] auto y() const -> double;

  [[nodiscard]] auto z() const -> double;

  [[nodiscard]] auto e() const -> double;

  [[nodiscard]] auto n() const -> double;

  [[nodiscard]] auto u() const -> double;

}; // class enu_t

} // namespace tybl::coord

#endif // TYBL_COORD_ENU_HPP

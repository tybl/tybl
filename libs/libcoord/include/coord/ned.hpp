// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COORD_NED_HPP
#define TYBL_COORD_NED_HPP

#include "lynel/basic_matrix.hpp"

namespace tybl::coord {

class ecef_t;

class ned_t {
  lynel::cvec3<double> m_ned;

public:
  auto to_ecef(ecef_t const& p_ref_pos) const -> ecef_t;

  auto x() const -> double;

  auto y() const -> double;

  auto z() const -> double;

  auto n() const -> double;

  auto e() const -> double;

  auto d() const -> double;

}; // class ned_t

} // namespace tybl::coord

#endif // TYBL_COORD_NED_HPP
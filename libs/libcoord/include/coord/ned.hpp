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
  [[nodiscard,gnu::pure]] auto to_ecef(ecef_t const& p_ref_pos) const -> ecef_t;

  [[nodiscard,gnu::pure]] auto x() const -> double;

  [[nodiscard,gnu::pure]] auto y() const -> double;

  [[nodiscard,gnu::pure]] auto z() const -> double;

  [[nodiscard,gnu::pure]] auto n() const -> double;

  [[nodiscard,gnu::pure]] auto e() const -> double;

  [[nodiscard,gnu::pure]] auto d() const -> double;

}; // class ned_t

} // namespace tybl::coord

#endif // TYBL_COORD_NED_HPP

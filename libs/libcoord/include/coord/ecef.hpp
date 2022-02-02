// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COORD_ECEF_HPP
#define TYBL_COORD_ECEF_HPP

#include "lynel/basic_matrix.hpp"

namespace tybl::coord {

class lla_t;

class ecef_t {
  lynel::cvec3<double> m_ecef;

public:
  explicit ecef_t(lynel::cvec3<double> p_pos);

  [[nodiscard,gnu::pure]] explicit operator lynel::cvec3<double>() const;

  [[nodiscard,gnu::pure]] auto to_lla() const -> lla_t;

  [[nodiscard,gnu::pure]] auto x() const -> double;

  [[nodiscard,gnu::pure]] auto y() const -> double;

  [[nodiscard,gnu::pure]] auto z() const -> double;

}; // class ecef_t

} // namespace tybl::coord

#endif // TYBL_COORD_ECEF_HPP

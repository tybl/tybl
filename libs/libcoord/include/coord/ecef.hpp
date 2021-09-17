// License: The Unlicense (https://unlicense.org)
#pragma once

#include "lynel/basic_matrix.hpp"

namespace tybl::coord {

class lla_t;

class ecef_t {
  lynel::cvec3<double> ecef;
public:

  explicit ecef_t(lynel::cvec3<double> pos);

  operator lynel::cvec3<double>() const;

  auto to_lla() const -> lla_t;

  auto x() const -> double;

  auto y() const -> double;

  auto z() const -> double;

}; // class ecef_t

} // namespace tybl::coord

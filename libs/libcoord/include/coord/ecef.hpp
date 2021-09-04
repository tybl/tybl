// License: The Unlicense (https://unlicense.org)
#pragma once

#include "lynel/vec3d.hpp"

namespace tybl::coord {

class lla_t;

class ecef_t {
  lynel::vec3d ecef;
public:

  explicit ecef_t(lynel::vec3d pos);

  operator lynel::vec3d() const;

  auto to_lla() const -> lla_t;

  auto x() const -> double;

  auto y() const -> double;

  auto z() const -> double;

}; // class ecef_t

} // namespace tybl::coord

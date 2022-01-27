// License: The Unlicense (https://unlicense.org)
#include "coord/lla.hpp"

#include "coord/ecef.hpp"

#include <stdexcept>

namespace tybl::coord {

auto lla_t::to_ecef() const -> ecef_t {
  static_cast<void>(this);
  // TODO(tybl): Implement this function
  throw std::runtime_error(__func__); // NOLINT`
}

auto lla_t::latitude() const -> double { return m_latitude; }

auto lla_t::longitude() const -> double { return m_longitude; }

auto lla_t::altitude() const -> double { return m_altitude; }

} // namespace tybl::coord

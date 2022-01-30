// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COORD_LLA_HPP
#define TYBL_COORD_LLA_HPP

namespace tybl::coord {

class ecef_t;

class lla_t {
  double m_latitude;
  double m_longitude;
  double m_altitude;

public:
  [[nodiscard]] auto to_ecef() const -> ecef_t;

  [[nodiscard]] auto latitude() const -> double;

  [[nodiscard]] auto longitude() const -> double;

  [[nodiscard]] auto altitude() const -> double;

}; // class lla_c

} // namespace tybl::coord

#endif // TYBL_COORD_LLA_HPP

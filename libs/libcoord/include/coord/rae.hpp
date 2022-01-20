// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COORD_RAE_HPP
#define TYBL_COORD_RAE_HPP

namespace tybl::coord {

class frd_t;

class rae_t {
  double m_range;
  double m_azimuth;
  double m_elevation;

public:
  rae_t(double p_r, double p_a, double p_e);

  auto to_frd() const -> frd_t;

  auto range() const -> double;

  auto azimuth() const -> double;

  auto elevation() const -> double;

}; // class rae_t

} // namespace tybl::coord

#endif // TYBL_COORD_RAE_HPP
// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_LATESTSTATE_HPP
#define TYBL_NMEA_LATESTSTATE_HPP

#include "state.hpp"

struct latest_state : public state {

  ~latest_state() override;

  void apply_gga(gga_sentence const& p_sentence) override;

  void apply_gsa(gsa_sentence const& p_sentence) override;

  void apply_gsv(gsv_sentence const& p_sentence) override;

  void apply_rmc(rmc_sentence const& p_sentence) override;

  void apply_vtg(vtg_sentence const& p_sentence) override;

  [[nodiscard]] auto latitude() const -> float;

  [[nodiscard]] auto longitude() const -> float;

private:
  float m_time_of_day;
  int m_date;
  float m_latitude;
  float m_longitude;
  int m_fix_quality;
  int m_num_satellites;
  float m_horizontal_dilution_of_precision;
  float m_height_above_ellipsoid;
  float m_time_since_last_dgps_update;
  float m_speed_kts;
  int m_dgps_reference_station_id;
  float m_course;
  float m_magnetic_variation;
}; // class latest_state

#endif // TYBL_NMEA_LATESTSTATE_HPP

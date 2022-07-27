// License: The Unlicense (https://unlicense.org)
#include <nmea/v2/latest_state.hpp>

latest_state::~latest_state() = default;

void latest_state::apply_gga(gga_sentence const& p_sentence) {
  m_time_of_day = p_sentence.time_of_day;
  m_latitude = p_sentence.latitude;
  m_longitude = p_sentence.longitude;
  m_fix_quality = p_sentence.fix_quality;
  m_num_satellites = p_sentence.num_satellites;
  m_horizontal_dilution_of_precision = p_sentence.horizontal_dilution_of_precision;
  m_height_above_ellipsoid = p_sentence.height_above_ellipsoid;
  m_time_since_last_dgps_update = p_sentence.time_since_last_dgps_update;
  m_dgps_reference_station_id = p_sentence.dgps_reference_station_id;
}

void latest_state::apply_gsa(gsa_sentence const& /*p_sentence*/) {
  // TODO
}

void latest_state::apply_gsv(gsv_sentence const& /*p_sentence*/) {
  // TODO
}

void latest_state::apply_rmc(rmc_sentence const& p_sentence) {
  m_time_of_day = p_sentence.time;
  m_latitude = p_sentence.latitude;
  m_longitude = p_sentence.longitude;
  m_speed_kts = p_sentence.speed;
  m_course = p_sentence.course;
  m_date = p_sentence.date;
  m_magnetic_variation = p_sentence.magnetic_variation;
}

void latest_state::apply_vtg(vtg_sentence const& p_sentence) {
  m_speed_kts = p_sentence.speed_over_ground_kts;
}

auto latest_state::latitude() const -> float { return m_latitude; }

auto latest_state::longitude() const -> float { return m_longitude; }

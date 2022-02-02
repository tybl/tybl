// License: The Unlicense (https://unlicense.org)
#include "gps/almanac.hpp"

#include <vodka/algorithm/max.hpp>

namespace gps {

void almanac::clear() {
  m_total_pages = 0;
  m_processed_pages = 0;
  m_visible_size = 0;
  satellites.clear();
}

void almanac::update_satellite(gps::satellite const& p_sat) {
  if (satellites.size() > m_visible_size) { // we missed the new almanac start page, start over.
    clear();
  }

  satellites.push_back(p_sat);
}

auto almanac::percent_complete() const -> double {
  if (m_total_pages == 0) {
    return 0.0;
  }

  return static_cast<double>(m_processed_pages) / m_total_pages * 100.0;
}

auto almanac::average_snr() const -> double {

  double avg = 0;
  double relevant = 0;
  for (const auto& satellite : satellites) {
    if (satellite.snr > 0) {
      relevant += 1.0;
    }
  }

  for (const auto& satellite : satellites) {
    if (satellite.snr > 0) {
      avg += satellite.snr / relevant;
    }
  }

  return avg;
}

auto almanac::min_snr() const -> double {
  double min = 9999999;
  if (satellites.empty()) {
    return 0;
  }
  int32_t num_over_zero = 0;
  for (const auto& satellite : satellites) {
    if (satellite.snr > 0) {
      num_over_zero++;
      if (satellite.snr < min) {
        min = satellite.snr;
      }
    }
  }
  if (num_over_zero == 0) {
    return 0;
  }
  return min;
}

auto almanac::max_snr() const -> double {
  double max = 0;
  for (const auto& satellite : satellites) {
    max = tybl::vodka::max(max, satellite.snr);
  }
  return max;
}

} // namespace gps

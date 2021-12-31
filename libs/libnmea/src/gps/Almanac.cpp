#include "gps/Almanac.hpp"

namespace gps {

Almanac::Almanac()
  : m_total_pages(0)
  , m_processed_pages(0)
{}

void Almanac::clear() {
  m_total_pages = 0;
  m_processed_pages = 0;
  m_visible_size = 0;
  satellites.clear();
}

void Almanac::update_satellite(gps::Satellite sat) {
  if (satellites.size() >
      m_visible_size)
  {  //we missed the new almanac start page, start over.
    clear();
  }

  satellites.push_back(sat);
}

double Almanac::percent_complete() {
  if (m_total_pages == 0) {
    return 0.0;
  }

  return static_cast<double>(m_processed_pages) / m_total_pages * 100.0;
}

double Almanac::average_snr() {

  double avg = 0;
  double relevant = 0;
  for (const auto& satellite : satellites){
    if (satellite.snr > 0) {
      relevant += 1.0;
    }
  }

  for (const auto& satellite : satellites){
    if (satellite.snr > 0) {
      avg += satellite.snr / relevant;
    }
  }

  return avg;
}

double Almanac::min_snr() {
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

double Almanac::max_snr() {
  double max = 0;
  for (const auto& satellite : satellites) {
    if (satellite.snr > 0) {
      if (satellite.snr > max) {
        max = satellite.snr;
      }
    }
  }
  return max;
}

} // namespace gps

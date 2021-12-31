#include "gps/Almanac.hpp"

namespace gps {

Almanac::Almanac()
  : lastPage(0)
  , totalPages(0)
  , processedPages(0)
{}

void Almanac::clear() {
  lastPage = 0;
  totalPages = 0;
  processedPages = 0;
  visibleSize = 0;
  satellites.clear();
}

void Almanac::updateSatellite(gps::Satellite sat) {
  if (satellites.size() > visibleSize)
  {  //we missed the new almanac start page, start over.
    clear();
  }

  satellites.push_back(sat);
}

double Almanac::percentComplete() {
  if (totalPages == 0) {
    return 0.0;
  }

  return ((double)processedPages) / ((double)totalPages) * 100.0;
}

double Almanac::averageSNR() {

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

double Almanac::minSNR() {
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

double Almanac::maxSNR() {
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

#pragma once

#include "gps/Satellite.hpp"

#include <cstdint>
#include <vector>

namespace nmea {
  class GPSService;
} // namespace nmea

namespace gps {

class Almanac {
  friend nmea::GPSService;
private:
  uint32_t visibleSize;
  uint32_t lastPage;
  uint32_t totalPages;
  uint32_t processedPages;
  void clear();      //will remove all information from the satellites
  void updateSatellite(gps::Satellite sat);
public:
  Almanac();

  //mapped by prn
  std::vector<gps::Satellite> satellites;
  double averageSNR();
  double minSNR();
  double maxSNR();
  double percentComplete();

}; // class Almanac

} // namespace gps

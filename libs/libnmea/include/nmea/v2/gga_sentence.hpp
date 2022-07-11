// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_GGASENTENCE_HPP
#define TYBL_NMEA_GGASENTENCE_HPP

struct gga_sentence {
  float time_of_day;
  float latitude;
  float longitude;
  int fix_quality;
  int num_satellites;
  float horizontal_dilution_of_precision;
  float height_above_ellipsoid;
  float time_since_last_dgps_update;
  int dgps_reference_station_id;
};

#endif // TYBL_NMEA_GGASENTENCE_HPP

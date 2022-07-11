// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_SATELLITEINVIEW_HPP
#define TYBL_NMEA_SATELLITEINVIEW_HPP

struct satellite_in_view {
  int prn_number;
  double elevation;
  double azimuth;
  double signal_to_noise_ratio;
};

#endif // TYBL_NMEA_SATELLITEINVIEW_HPP

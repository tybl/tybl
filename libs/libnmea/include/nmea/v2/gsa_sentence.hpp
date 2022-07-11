// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_GSASENTENCE_HPP
#define TYBL_NMEA_GSASENTENCE_HPP

#include <vector>

struct gsa_sentence {
  enum class Mode {
    FIX_UNAVAILABLE,
    AUTOMATIC_2D,
    AUTOMATIC_3D,
    MANUAL_2D,
    MANUAL_3D,
  } mode;
  std::vector<int> active_satellite_ids;
  float dilution_of_precision;
  float horizontal_dilution_of_precision;
  float vertical_dilution_of_precision;
};

#endif // TYBL_NMEA_GSASENTENCE_HPP

// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_GSVSENTENCE_HPP
#define TYBL_NMEA_GSVSENTENCE_HPP

#include "satellite_in_view.hpp"

#include <vector>

struct gsv_sentence {
  std::vector<satellite_in_view> satellites_in_view;
};

#endif // TYBL_NMEA_GSVSENTENCE_HPP

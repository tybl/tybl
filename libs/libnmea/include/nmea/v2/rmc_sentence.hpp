// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_RMCSENTENCE_HPP
#define TYBL_NMEA_RMCSENTENCE_HPP

struct rmc_sentence {
  float time;
  int date;
  float latitude;
  float longitude;
  float speed;
  float course;
  float magnetic_variation;
  bool valid;
};

#endif // TYBL_NMEA_RMCSENTENCE_HPP

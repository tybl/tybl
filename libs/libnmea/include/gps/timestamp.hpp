// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_GPS_TIMESTAMP_HPP
#define TYBL_NMEA_GPS_TIMESTAMP_HPP

#include <cstdint>
#include <string>

namespace gps {

class timestamp {
  std::string month_name(int32_t p_index);
public:
  timestamp();

  int32_t hour;
  int32_t min;
  double sec;

  int32_t month;
  int32_t day;
  int32_t year;

  // Values collected directly from the GPS
  double raw_time;
  int32_t raw_date;

  time_t get_time();

  // Set directly from the NMEA time stamp
  // hhmmss.sss
  void set_time(double p_raw_ts);

  // Set directly from the NMEA date stamp
  // ddmmyy
  void set_date(int32_t p_raw_date);

  std::string to_string();
}; // class timestamp

} // namespace gps

#endif // TYBL_NMEA_GPS_TIMESTAMP_HPP
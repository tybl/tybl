#pragma once

#include <cstdint>
#include <string>

namespace gps {

class Timestamp {
  std::string monthName(uint32_t index);
public:
  Timestamp();

  int32_t hour;
  int32_t min;
  double sec;

  int32_t month;
  int32_t day;
  int32_t year;

  // Values collected directly from the GPS
  double rawTime;
  int32_t rawDate;

  time_t getTime();

  // Set directly from the NMEA time stamp
  // hhmmss.sss
  void setTime(double raw_ts);

  // Set directly from the NMEA date stamp
  // ddmmyy
  void setDate(int32_t raw_date);

  std::string toString();
}; // class Timestamp

} // namespace gps

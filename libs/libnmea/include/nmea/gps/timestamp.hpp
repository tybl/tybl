// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_GPS_TIMESTAMP_HPP
#define TYBL_NMEA_GPS_TIMESTAMP_HPP

#include <cstdint>
#include <string>

namespace tybl::nmea::gps {

class timestamp {
  static auto month_name(int32_t p_index) -> std::string;

public:
  timestamp();

  int32_t hour{0};
  int32_t min{0};
  double sec{0};

  int32_t month{1};
  int32_t day{1};
  int32_t year{1970};

  // Values collected directly from the GPS
  double raw_time{0};
  int32_t raw_date{0};

  [[nodiscard]] auto get_time() const -> time_t;

  // Set directly from the NMEA time stamp
  // hhmmss.sss
  void set_time(double p_raw_ts);

  // Set directly from the NMEA date stamp
  // ddmmyy
  void set_date(int32_t p_raw_date);

  [[nodiscard]] auto to_string() const -> std::string;
}; // class timestamp

} // namespace tybl::nmea::gps

#endif // TYBL_NMEA_GPS_TIMESTAMP_HPP

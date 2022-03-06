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

  [[nodiscard]] auto get_time() const -> time_t;

  // Set directly from the NMEA time stamp
  // hhmmss.sss
  void set_time(double p_raw_ts);

  // Set directly from the NMEA date stamp
  // ddmmyy
  void set_date(int32_t p_raw_date);

  [[nodiscard]] auto to_string() const -> std::string;

  [[nodiscard]] auto raw_date() const noexcept -> int32_t { return m_raw_date; }
  [[nodiscard]] auto raw_time() const noexcept -> double { return m_raw_time; }
  [[nodiscard]] auto year() const noexcept -> int32_t { return m_year; }
  [[nodiscard]] auto month() const noexcept -> int32_t { return m_month; }
  [[nodiscard]] auto day() const noexcept -> int32_t { return m_day; }
  [[nodiscard]] auto hour() const noexcept -> int32_t { return m_hour; }
  [[nodiscard]] auto min() const noexcept -> int32_t { return m_min; }
  [[nodiscard]] auto sec() const noexcept -> double { return m_sec; }

private:
  double m_raw_time{0.0};
  double m_sec{0};
  int32_t m_min{0};
  int32_t m_hour{0};
  int32_t m_day{1};
  int32_t m_month{1};
  int32_t m_year{1970};
  int32_t m_raw_date{0};
}; // class timestamp

} // namespace tybl::nmea::gps

#endif // TYBL_NMEA_GPS_TIMESTAMP_HPP
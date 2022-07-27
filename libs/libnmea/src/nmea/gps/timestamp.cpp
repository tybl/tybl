// License: The Unlicense (https://unlicense.org)
#include <nmea/gps/timestamp.hpp>

#include <array>
#include <cmath> // trunc
#include <ctime>
#include <sstream>

namespace tybl::nmea::gps {

// indexed from 1!
auto timestamp::month_name(int32_t p_index) -> std::string {
  if (p_index < 1 || p_index > 12) {
    std::stringstream ss;
    ss << "[month:" << p_index << "]";
    return ss.str();
  }

  std::array<std::string, 12> names = {"January", "February", "March",     "April",   "May",      "June",
                                       "July",    "August",   "September", "October", "November", "December"};
  return names.at(static_cast<size_t>(p_index - 1));
}

// Returns seconds since Jan 1, 1970. Classic Epoch time.
auto timestamp::get_time() const -> time_t {
  std::tm t{};
  t.tm_year = year() - 1900; // This is year-1900, so 112 = 2012
  t.tm_mon = month();        // month from 0:Jan
  t.tm_mday = day();
  t.tm_hour = hour();
  t.tm_min = min();
  t.tm_sec = static_cast<int>(sec());
  return mktime(&t);
}

void timestamp::set_time(double p_raw_ts) {
  m_raw_time = p_raw_ts;

  m_hour = static_cast<int32_t>(p_raw_ts / 10000.0);
  m_min = static_cast<int32_t>((p_raw_ts - hour() * 10000) / 100.0);
  m_sec = p_raw_ts - min() * 100 - hour() * 10000;
}

// ddmmyy
void timestamp::set_date(int32_t p_raw_date) {
  m_raw_date = p_raw_date;
  // If uninitialized, use posix time.
  if (m_raw_date == 0) {
    m_month = 1;
    m_day = 1;
    m_year = 1970;
  } else {
    m_day = static_cast<int32_t>(p_raw_date / 10000.0);
    m_month = static_cast<int32_t>((p_raw_date - 10000 * day()) / 100.0);
    m_year = p_raw_date - 10000 * day() - 100 * month() + 2000;
  }
}

auto timestamp::to_string() const -> std::string {
  std::stringstream ss;
  ss << hour() << "h " << min() << "m " << sec() << "s"
     << "  " << month_name(month()) << " " << day() << " " << year();
  return ss.str();
}

} // namespace tybl::nmea::gps
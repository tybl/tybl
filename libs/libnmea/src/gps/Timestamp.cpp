#include "gps/Timestamp.hpp"

#include <cmath> // trunc
#include <sstream>

namespace gps {

Timestamp::Timestamp() {
  hour = 0;
  min = 0;
  sec = 0;

  month = 1;
  day = 1;
  year = 1970;

  rawTime = 0;
  rawDate = 0;
}

// indexed from 1!
std::string Timestamp::month_name(uint32_t index) {
  if (index < 1 || index > 12) {
    std::stringstream ss;
    ss << "[month:" << index << "]";
    return ss.str();
  }

  std::string names[] = {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
  };
  return names[index - 1];
}

// Returns seconds since Jan 1, 1970. Classic Epoch time.
time_t Timestamp::getTime() {
  struct tm t = { 0 };
  t.tm_year = year - 1900;  // This is year-1900, so 112 = 2012
  t.tm_mon = month;      // month from 0:Jan
  t.tm_mday = day;
  t.tm_hour = hour;
  t.tm_min = min;
  t.tm_sec = static_cast<int>(sec);
  return mktime(&t);
}

void Timestamp::setTime(double raw_ts) {
  rawTime = raw_ts;

  hour = (int32_t)trunc(raw_ts / 10000.0);
  min = (int32_t)trunc((raw_ts - hour * 10000) / 100.0);
  sec = raw_ts - min * 100 - hour * 10000;
}

//ddmmyy
void Timestamp::setDate(int32_t raw_date) {
  rawDate = raw_date;
  // If uninitialized, use posix time.
  if(rawDate == 0) {
    month = 1;
    day = 1;
    year = 1970;
  } else {
    day = (int32_t)trunc(raw_date / 10000.0);
    month = (int32_t)trunc((raw_date - 10000 * day) / 100.0);
    year = raw_date - 10000 * day - 100 * month + 2000;
  }
}

std::string Timestamp::to_string() {
  std::stringstream ss;
  ss << hour << "h " << min << "m " << sec << "s" << "  " << month_name(month) << " " << day << " " << year;
  return ss.str();
}

} // namespace gps

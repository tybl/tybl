// License: The Unlicense (https://unlicense.org)
#include <nmea/gps/fix.hpp>

//#include "gps/satellite.hpp"

#include <array>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

namespace tybl::nmea::gps {

// Searching...
// Void
// 1=none, 2=2d, 3=3d

// Horizontal - Best is 1, >20 is terrible, so 0 means uninitialized

// Returns the duration since the Host has received information
auto fix::time_since_last_update() const -> std::chrono::seconds {
  time_t now = time(nullptr);
  std::tm stamp{};

  stamp.tm_hour = m_timestamp.hour();
  stamp.tm_min = m_timestamp.min();
  stamp.tm_sec = static_cast<int>(m_timestamp.sec());
  stamp.tm_year = m_timestamp.year() - 1900;
  stamp.tm_mon = m_timestamp.month() - 1;
  stamp.tm_mday = m_timestamp.day();

  time_t then = mktime(&stamp);
  auto secs = static_cast<uint64_t>(difftime(now, then));
  return std::chrono::seconds(secs);
}

auto fix::has_estimate() const -> bool { return (latitude != 0 && longitude != 0) || (quality == 6); }

auto fix::set_lock(bool p_lock) -> bool {
  if (m_has_lock != p_lock) {
    m_has_lock = p_lock;
    return true;
  }
  return false;
}

auto fix::locked() const -> bool { return m_has_lock; }

// Returns meters
auto fix::horizontal_accuracy() const -> double {
  // horizontal 2drms 95% = 4.0  -- from GPS CHIP datasheets
  return 4.0 * horizontal_dilution;
}

// Returns meters
auto fix::vertical_accuracy() const -> double {
  // Vertical 2drms 95% = 6.0  -- from GPS CHIP datasheets
  return 6.0 * vertical_dilution;
}

// Takes a degree travel heading (0-360') and returns the name
auto fix::ordinal_direction(double p_deg, bool p_abbrev) -> std::string {

  // normalize, just in case
  auto c = static_cast<int32_t>(round(p_deg / 360.0 * 8.0));
  int32_t r = c % 8;
  if (r < 0) {
    r = 8 + r;
  }

  if (p_abbrev) {

    std::array<std::string, 9> dirs = {"N", "NE", "E", "SE", "S", "SW", "W", "NW", "N"};
    return dirs[r];
  }
  std::array<std::string, 9> dirs = {"North",      "North East", "East",       "South East", "South",
                                     "South West", "West",       "North West", "North"};
  return dirs[r];
}

auto fix_status_to_string(char p_status) -> std::string {
  switch (p_status) {
    case 'A': return "Active";
    case 'V': return "Void";
    default: return "Unknown";
  }
}

auto fix_type_to_string(uint8_t p_type) -> std::string {
  switch (p_type) {
    case 1: return "None";
    case 2: return "2D";
    case 3: return "3D";
    default: return "Unknown";
  }
}

auto fix_quality_to_string(uint8_t p_quality) -> std::string {
  switch (p_quality) {
    case 0: return "Invalid";
    case 1: return "Standard";
    case 2: return "DGPS";
    case 3: return "PPS fix";
    case 4: return "Real Time Kinetic";
    case 5: return "Real Time Kinetic (float)";
    case 6: return "Estimate";
    default: return "Unknown";
  }
}

auto fix::to_string() -> std::string {
  std::stringstream ss;
  std::ios_base::fmtflags oldflags = ss.flags();

  ss << "========================== GPS FIX ================================" << std::endl
     << " Status: \t\t" << (m_has_lock ? "LOCK!" : "SEARCHING...") << std::endl
     << " Satellites: \t\t" << tracking_satellites << " (tracking) of " << visible_satellites << " (visible)"
     << std::endl
     << " < fix Details >" << std::endl
     << "   Age:                " << time_since_last_update().count() << " s" << std::endl
     << "   timestamp:          " << m_timestamp.to_string() << "   UTC   \n\t\t\t(raw: " << m_timestamp.raw_time()
     << " time, " << m_timestamp.raw_date() << " date)" << std::endl
     << "   Raw Status:         " << status << "  (" << fix_status_to_string(status) << ")" << std::endl
     << "   Type:               " << static_cast<int>(type) << "  (" << fix_type_to_string(type) << ")" << std::endl
     << "   Quality:            " << static_cast<int>(quality) << "  (" << fix_quality_to_string(quality) << ")"
     << std::endl
     << "   Lat/Lon (N,E):      " << std::setprecision(6) << std::fixed << latitude << "' N, " << longitude << "' E"
     << std::endl;

  ss.flags(oldflags); // reset

  ss << "   DOP (P,H,V):        " << dilution << ",   " << horizontal_dilution << ",   " << vertical_dilution
     << std::endl
     << "   Accuracy(H,V):      " << horizontal_accuracy() << " m,   " << vertical_accuracy() << " m" << std::endl;

  ss << "   Altitude:           " << altitude << " m" << std::endl
     << "   Speed:              " << speed << " km/h" << std::endl
     << "   Travel Dir:         " << travel_angle << " deg  [" << ordinal_direction(travel_angle) << "]" << std::endl
     << "   SNR:                avg: " << m_almanac.average_snr() << " dB   [min: " << m_almanac.min_snr()
     << " dB,  max:" << m_almanac.max_snr() << " dB]" << std::endl;

  ss << " < almanac (" << m_almanac.percent_complete() << "%) >" << std::endl;
  if (m_almanac.satellites.empty()) {
    ss << " > No satellite info in almanac." << std::endl;
  }
  for (size_t i = 0; i < m_almanac.satellites.size(); i++) {
    ss << "   [" << std::setw(2) << std::setfill(' ') << (i + 1) << "]   " << m_almanac.satellites[i].to_string()
       << std::endl;
  }

  return ss.str();
}

fix::operator std::string() { return to_string(); }

} // namespace tybl::nmea::gps
// License: The Unlicense (https://unlicense.org)
#include "gps/fix.hpp"

//#include "gps/satellite.hpp"

#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

namespace gps {

fix::fix()
  : m_has_lock(false)
{
  quality = 0;  // Searching...
  status = 'V';  // Void
  type = 1;    // 1=none, 2=2d, 3=3d

  dilution = 0;
  horizontal_dilution = 0;    // Horizontal - Best is 1, >20 is terrible, so 0 means uninitialized
  vertical_dilution = 0;
  latitude = 0;  
  longitude = 0;  
  speed = 0;
  travel_angle = 0;
  altitude = 0;
  tracking_satellites = 0;
  visible_satellites = 0;
}

fix::~fix() {
  // TODO Auto-generated destructor stub
}

// Returns the duration since the Host has received information
std::chrono::seconds fix::time_since_last_update(){
  time_t now = time(NULL);
  std::tm stamp{};

  stamp.tm_hour = timestamp.hour;
  stamp.tm_min = timestamp.min;
  stamp.tm_sec = static_cast<int>(timestamp.sec);
  stamp.tm_year = timestamp.year-1900;
  stamp.tm_mon = timestamp.month-1;
  stamp.tm_mday = timestamp.day;

  time_t then = mktime(&stamp);
  auto secs = static_cast<uint64_t>(difftime(now,then));
  return std::chrono::seconds(secs);
}

bool fix::has_estimate(){
  return (latitude != 0 && longitude != 0) || (quality == 6);
}

bool fix::set_lock(bool p_locked){
  if (m_has_lock != p_locked){
    m_has_lock = p_locked;
    return true;
  }
  return false;
}

bool fix::locked(){
  return m_has_lock;
}

// Returns meters
double fix::horizontal_accuracy(){
  // horizontal 2drms 95% = 4.0  -- from GPS CHIP datasheets
  return 4.0 * horizontal_dilution;
}

// Returns meters
double fix::vertical_accuracy(){
  // Vertical 2drms 95% = 6.0  -- from GPS CHIP datasheets
  return 6.0 * vertical_dilution;
}

// Takes a degree travel heading (0-360') and returns the name
std::string fix::ordinal_direction(double p_deg, bool p_abbrev){

  //normalize, just in case
  auto c = static_cast<int32_t>(round(p_deg / 360.0 * 8.0));
  int32_t r = c % 8;
  if (r < 0){
    r = 8 + r;
  }

  if (p_abbrev){
    std::string dirs[] = {
      "N",
      "NE",
      "E",
      "SE",
      "S",
      "SW",
      "W",
      "NW",
      "N"
    };
    return dirs[r];
  } else {
    std::string dirs[] = {
      "North",
      "North East",
      "East",
      "South East",
      "South",
      "South West",
      "West",
      "North West",
      "North"
    };
    return dirs[r];
  }
  
}

std::string fix_status_to_string(char p_status){
  switch (p_status){
  case 'A':
    return "Active";
  case 'V':
    return "Void";
  default:
    return "Unknown";
  }
}

std::string fix_type_to_string(uint8_t p_type){
  switch (p_type){
  case 1:
    return "None";
  case 2:
    return "2D";
  case 3:
    return "3D";
  default:
    return "Unknown";
  }
}

std::string fix_quality_to_string(uint8_t p_quality){
  switch (p_quality){
  case 0:
    return "Invalid";
  case 1:
    return "Standard";
  case 2:
    return "DGPS";
  case 3:
    return "PPS fix";
  case 4:
    return "Real Time Kinetic";
  case 5:
    return "Real Time Kinetic (float)";
  case 6:
    return "Estimate";
  default:
    return "Unknown";
  }
}

std::string fix::to_string(){
  std::stringstream ss;
  std::ios_base::fmtflags oldflags = ss.flags();

  ss << "========================== GPS FIX ================================" << std::endl
    << " Status: \t\t" << ((m_has_lock) ? "LOCK!" : "SEARCHING...") << std::endl
    << " Satellites: \t\t" << tracking_satellites << " (tracking) of " << visible_satellites << " (visible)" << std::endl
    << " < fix Details >" << std::endl
    << "   Age:                " << time_since_last_update().count() << " s" << std::endl
    << "   timestamp:          " << timestamp.to_string() << "   UTC   \n\t\t\t(raw: " << timestamp.rawTime << " time, " << timestamp.rawDate << " date)" << std::endl
    << "   Raw Status:         " << status      << "  (" << fix_status_to_string(status) << ")" << std::endl
    << "   Type:               " << static_cast<int>(type)    << "  (" << fix_type_to_string(type) << ")" << std::endl
    << "   Quality:            " << static_cast<int>(quality)  << "  (" << fix_quality_to_string(quality) << ")" << std::endl
    << "   Lat/Lon (N,E):      " << std::setprecision(6) << std::fixed << latitude << "' N, " << longitude << "' E" <<  std::endl;

  ss.flags(oldflags);  //reset

  ss << "   DOP (P,H,V):        " << dilution << ",   " << horizontal_dilution
     << ",   " << vertical_dilution << std::endl
    << "   Accuracy(H,V):      " << horizontal_accuracy() << " m,   " << vertical_accuracy() << " m" << std::endl;

  ss << "   Altitude:           " << altitude << " m" << std::endl
    << "   Speed:              " << speed << " km/h" << std::endl
    << "   Travel Dir:         " << travel_angle << " deg  [" << ordinal_direction(travel_angle) << "]" << std::endl
    << "   SNR:                avg: " << almanac.average_snr() << " dB   [min: " << almanac.min_snr() << " dB,  max:" << almanac.max_snr() << " dB]" << std::endl;

  ss << " < almanac (" << almanac.percent_complete() << "%) >" << std::endl;
  if (almanac.satellites.empty()){
    ss << " > No satellite info in almanac." << std::endl;
  }
  for (size_t i = 0; i < almanac.satellites.size(); i++){
    ss << "   [" << std::setw(2) << std::setfill(' ') <<  (i + 1) << "]   " << almanac.satellites[i].to_string() << std::endl;
  }

  return ss.str();
}

fix::operator std::string(){
  return to_string();
}

} // namespace gps

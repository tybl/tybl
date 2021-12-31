#include "gps/Fix.hpp"

#include "gps/Satellite.hpp"

#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

namespace gps {

Fix::Fix()
  : m_haslock(false)
{
  quality = 0;  // Searching...
  status = 'V';  // Void
  type = 1;    // 1=none, 2=2d, 3=3d

  dilution = 0;    
  horizontalDilution = 0;    // Horizontal - Best is 1, >20 is terrible, so 0 means uninitialized
  verticalDilution = 0;  
  latitude = 0;  
  longitude = 0;  
  speed = 0;
  travelAngle = 0;
  altitude = 0;
  trackingSatellites = 0;
  visibleSatellites = 0;
}

Fix::~Fix() {
  // TODO Auto-generated destructor stub
}

// Returns the duration since the Host has received information
std::chrono::seconds Fix::timeSinceLastUpdate(){
  time_t now = time(NULL);
  struct tm stamp = { 0 };

  stamp.tm_hour = timestamp.hour;
  stamp.tm_min = timestamp.min;
  stamp.tm_sec = (int)timestamp.sec;
  stamp.tm_year = timestamp.year-1900;
  stamp.tm_mon = timestamp.month-1;
  stamp.tm_mday = timestamp.day;

  time_t then = mktime(&stamp);
  uint64_t secs = (uint64_t)difftime(now,then);
  return std::chrono::seconds((uint64_t)secs);
}

bool Fix::hasEstimate(){
  return (latitude != 0 && longitude != 0) || (quality == 6);
}

bool Fix::setlock(bool locked){
  if (m_haslock != locked){
    m_haslock = locked;
    return true;
  }
  return false;
}

bool Fix::locked(){
  return m_haslock;
}

// Returns meters
double Fix::horizontalAccuracy(){
  // horizontal 2drms 95% = 4.0  -- from GPS CHIP datasheets
  return 4.0 * horizontalDilution;
}

// Returns meters
double Fix::verticalAccuracy(){
  // Vertical 2drms 95% = 6.0  -- from GPS CHIP datasheets
  return 6.0 * verticalDilution;
}

// Takes a degree travel heading (0-360') and returns the name
std::string Fix::travelAngleToCompassDirection(double deg, bool abbrev){

  //normalize, just in case
  int32_t c = (int32_t)round(deg / 360.0 * 8.0);
  int32_t r = c % 8;
  if (r < 0){
    r = 8 + r;
  }

  if (abbrev){
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
  
};

std::string fixStatusToString(char status){
  switch (status){
  case 'A':
    return "Active";
  case 'V':
    return "Void";
  default:
    return "Unknown";
  }
}

std::string fixTypeToString(uint8_t type){
  switch (type){
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

std::string fixQualityToString(uint8_t quality){
  switch (quality){
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

std::string Fix::toString(){
  std::stringstream ss;
  std::ios_base::fmtflags oldflags = ss.flags();

  ss << "========================== GPS FIX ================================" << std::endl
    << " Status: \t\t" << ((m_haslock) ? "LOCK!" : "SEARCHING...") << std::endl
    << " Satellites: \t\t" << trackingSatellites << " (tracking) of " << visibleSatellites << " (visible)" << std::endl
    << " < Fix Details >" << std::endl
    << "   Age:                " << timeSinceLastUpdate().count() << " s" << std::endl
    << "   Timestamp:          " << timestamp.toString() << "   UTC   \n\t\t\t(raw: " << timestamp.rawTime << " time, " << timestamp.rawDate << " date)" << std::endl
    << "   Raw Status:         " << status      << "  (" << fixStatusToString(status) << ")" << std::endl
    << "   Type:               " << (int)type    << "  (" << fixTypeToString(type) << ")" << std::endl
    << "   Quality:            " << (int)quality  << "  (" << fixQualityToString(quality) << ")" << std::endl
    << "   Lat/Lon (N,E):      " << std::setprecision(6) << std::fixed << latitude << "' N, " << longitude << "' E" <<  std::endl;

  ss.flags(oldflags);  //reset

  ss << "   DOP (P,H,V):        " << dilution << ",   " << horizontalDilution << ",   " << verticalDilution << std::endl
    << "   Accuracy(H,V):      " << horizontalAccuracy() << " m,   " << verticalAccuracy() << " m" << std::endl;

  ss << "   Altitude:           " << altitude << " m" << std::endl
    << "   Speed:              " << speed << " km/h" << std::endl
    << "   Travel Dir:         " << travelAngle << " deg  [" << travelAngleToCompassDirection(travelAngle) << "]" << std::endl
    << "   SNR:                avg: " << almanac.averageSNR() << " dB   [min: " << almanac.minSNR() << " dB,  max:" << almanac.maxSNR() << " dB]" << std::endl;

  ss << " < Almanac (" << almanac.percentComplete() << "%) >" << std::endl;
  if (almanac.satellites.empty()){
    ss << " > No satellite info in almanac." << std::endl;
  }
  for (size_t i = 0; i < almanac.satellites.size(); i++){
    ss << "   [" << std::setw(2) << std::setfill(' ') <<  (i + 1) << "]   " << almanac.satellites[i].toString() << std::endl;
  }

  return ss.str();
}

Fix::operator std::string(){
  return toString();
}

} // namespace gps

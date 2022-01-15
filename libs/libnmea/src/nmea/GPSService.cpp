// License: The Unlicense (https://unlicense.org)
#include "nmea/GPSService.hpp"

#include "gps/satellite.hpp"
#include "nmea/parse_error.hpp"

#include <iostream>
#include <cmath>

namespace nmea {

// ------ Some helpers ----------
// Takes the NMEA lat/long format (dddmm.mmmm, [N/S,E/W]) and converts to degrees N,E only
static double convert_lat_lon_to_deg(std::string p_llstr, std::string p_dir) {

  double pd = std::stod(p_llstr);
  double deg = trunc(pd / 100);   //get ddd from dddmm.mmmm
  double mins = pd - deg * 100;

  deg = deg + mins / 60.0;

  char hdg = 'x';
  if (!p_dir.empty()) {
    hdg = p_dir[0];
  }

  //everything should be N/E, so flip S,W
  if (hdg == 'S' || hdg == 'W') {
    deg *= -1.0;
  }

  return deg;
}

static double kts_to_kph(double p_knots) {
  return p_knots * 1.852;
}

// ------------- GPSSERVICE CLASS -------------

GPSService::GPSService(Parser& p_parser) {
  attach_to_parser(p_parser);    // attach to parser in the GPS object
}

GPSService::~GPSService() = default;

void GPSService::attach_to_parser(Parser& p_parser) {

  // http://www.gpsinformation.org/dale/nmea.htm
  /* used sentences...
  $GPGGA    - time,position,fix data
  $GPGSA    - gps receiver operating mode, satellites used in position and DOP values
  $GPGSV    - number of gps satellites in view, satellite m_id, elevation,azimuth, and SNR
  $GPRMC    - time,date, position,course, and speed data
  $GPVTG    - course and speed information relative to the ground
  $GPZDA    - 1pps timing message
  $PSRF150  - gps module "ok to send"
  */
  p_parser.set_sentence_handler("PSRF150", [this](const sentence& p_nmea) {
    this->read_psrf150(p_nmea);
  });
  p_parser.set_sentence_handler("GPGGA", [this](const sentence& p_nmea) {
    this->read_gpgga(p_nmea);
  });
  p_parser.set_sentence_handler("GPGSA", [this](const sentence& p_nmea) {
    this->read_gpgsa(p_nmea);
  });
  p_parser.set_sentence_handler("GPGSV", [this](const sentence& p_nmea) {
    this->read_gpgsv(p_nmea);
  });
  p_parser.set_sentence_handler("GPRMC", [this](const sentence& p_nmea) {
    this->read_gprmc(p_nmea);
  });
  p_parser.set_sentence_handler("GPVTG", [this](const sentence& p_nmea) {
    this->read_gpvtg(p_nmea);
  });

}

void GPSService::read_psrf150(sentence const& /*p_nmea*/) {
  std::cerr << "GPSService::read_psrf150(sentence const&)\n";
  // nothing right now...
  // Called with checksum 3E (valid) for GPS turning ON
  // Called with checksum 3F (invalid) for GPS turning OFF
}

void GPSService::read_gpgga(sentence const& p_nmea) {
  std::cerr << "GPSService::read_gpgga(sentence const&)\n";
  /* -- EXAMPLE --
  $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47

  $GPGGA,205630.945,3346.1070,N,08423.6687,W,0,03,,30.8,M,-30.8,M,,0000*73    // ATLANTA!!!!

  Where:
  GGA          Global Positioning System fix Data
  index:
  [0] 123519       fix taken at 12:35:19 UTC
  [1-2] 4807.038,N   Latitude 48 deg 07.038' N
  [3-4] 1131.000,E  Longitude 11 deg 31.000' E
  [5] 1            fix quality: 0 = invalid
  1 = GPS fix (SPS)
  2 = DGPS fix
  3 = PPS fix
  4 = Real Time Kinematic
  5 = Float RTK
  6 = estimated (dead reckoning) (2.3 feature)
  7 = Manual input mode
  8 = Simulation mode
  [6] 08           Number of satellites being tracked
  [7] 0.9          Horizontal dilution of position
  [8-9] 545.4,M      Altitude, Meters, above mean sea level
  [10-11] 46.9,M       Height of geoid (mean sea level) above WGS84
  ellipsoid
  [12] (empty field) time in seconds since last DGPS update
  [13] (empty field) DGPS station m_id number
  [13]  *47          the checksum data, always begins with *
  */
  try {
    if (!p_nmea.is_checksum_ok()) {
      throw parse_error("Invalid checksum");
    }

    if (p_nmea.parameters.size() < 14) {
      throw parse_error("GPS data is missing parameters.");
    }

    // TIMESTAMP
    this->fix.timestamp.set_time(std::stod(p_nmea.parameters[0]));

    std::string sll;
    std::string dir;
    // LAT
    sll = p_nmea.parameters[1];
    dir = p_nmea.parameters[2];
    if (!sll.empty()) {
      this->fix.latitude = convert_lat_lon_to_deg(sll, dir);
    }

    // LONG
    sll = p_nmea.parameters[3];
    dir = p_nmea.parameters[4];
    if (!sll.empty()) {
      this->fix.longitude = convert_lat_lon_to_deg(sll, dir);
    }


    // FIX QUALITY
    bool lockupdate = false;
    fix.quality = static_cast<uint8_t>(std::stoul(p_nmea.parameters[5]));
    if (this->fix.quality == 0) {
      lockupdate = this->fix.set_lock(false);
    } else if (this->fix.quality == 1) {
      lockupdate = this->fix.set_lock(true);
    } else {}


    // TRACKING SATELLITES
    fix.tracking_satellites = std::stoi(p_nmea.parameters[6]);
    if (this->fix.visible_satellites < this->fix.tracking_satellites) {
      this->fix.visible_satellites = this->fix.tracking_satellites;    // the visible count is in another sentence.
    }

    // ALTITUDE
    if (!p_nmea.parameters[8].empty()) {
      this->fix.altitude = std::stod(p_nmea.parameters[8]);
    } else {
      // leave old value
    }

    //calling m_handlers
    if (lockupdate) {
      this->onLockStateChanged(this->fix.m_has_lock);
    }
    this->onUpdate();
  } catch (std::invalid_argument&) {
    parse_error pe("[$GPGGA] Could not convert string to a number", p_nmea);
    throw pe;
  } catch (parse_error& ex) {
    parse_error pe("GPS Data Bad Format [$GPGGA] :: " + ex.message, p_nmea);
    throw pe;
  }
}

void GPSService::read_gpgsa(sentence const& p_nmea) {
  std::cerr << "GPSService::read_gpgsa(sentence const&): " << __LINE__ << std::endl; //
  /*  -- EXAMPLE --
  $GPGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*39

  $GPGSA,A,3,18,21,22,14,27,19,,,,,,,4.4,2.7,3.4*32

  Where:
  GSA      satellite status
  [0] A        Auto selection of 2D or 3D fix (M = manual)
  [1] 3        3D fix - values include: 1 = no fix
  2 = 2D fix
  3 = 3D fix
  [2-13] 04,05... PRNs of satellites used for fix (space for 12)
  [14] 2.5      PDOP (dilution of precision)
  [15] 1.3      Horizontal dilution of precision (HDOP)
  [16] 2.1      Vertical dilution of precision (VDOP)
  [16] *39      the checksum data, always begins with *
  */

  try {
    std::cerr << "GPSService::read_gpgsa(sentence const&): " << __LINE__ << std::endl; //
    if (!p_nmea.is_checksum_ok()) {
      std::cerr << "GPSService::read_gpgsa(sentence const&): " << __LINE__ << std::endl;
      throw parse_error("Checksum is invalid!");
    }

    std::cerr << "GPSService::read_gpgsa(sentence const&): " << __LINE__ << std::endl; //
    if (p_nmea.parameters.size() < 17) {
      std::cerr << "GPSService::read_gpgsa(sentence const&): " << __LINE__ << std::endl;
      throw parse_error("GPS data is missing parameters.");
    }

    // FIX TYPE
    bool lockupdate = false;
    auto fix_type = std::stoul(p_nmea.parameters[1]);
    fix.type = static_cast<uint8_t>(fix_type);
    if (fix_type == 1) {
      std::cerr << "GPSService::read_gpgsa(sentence const&): " << __LINE__ << std::endl; //
      lockupdate = this->fix.set_lock(false);
    } else if (fix_type == 3) {
      std::cerr << "GPSService::read_gpgsa(sentence const&): " << __LINE__ << std::endl;
      lockupdate = this->fix.set_lock(true);
    } else {
      std::cerr << "GPSService::read_gpgsa(sentence const&): " << __LINE__ << std::endl;
    }

    // DILUTION OF PRECISION  -- PDOP
    double dop = std::stod(p_nmea.parameters[14]);
    this->fix.dilution = dop;
    std::cerr << "GPSService::read_gpgsa(sentence const&): " << __LINE__ << std::endl; //

    // HORIZONTAL DILUTION OF PRECISION -- HDOP
    double hdop = std::stod(p_nmea.parameters[15]);
    this->fix.horizontal_dilution = hdop;
    std::cerr << "GPSService::read_gpgsa(sentence const&): " << __LINE__ << std::endl; //

    // VERTICAL DILUTION OF PRECISION -- VDOP
    double vdop = std::stod(p_nmea.parameters[16]);
    this->fix.vertical_dilution = vdop;
    std::cerr << "GPSService::read_gpgsa(sentence const&): " << __LINE__ << std::endl; //

    //calling m_handlers
    if (lockupdate) {
      std::cerr << "GPSService::read_gpgsa(sentence const&): " << __LINE__ << std::endl;
      this->onLockStateChanged(this->fix.m_has_lock);
    }
    this->onUpdate();
  } catch (std::invalid_argument&) {
    std::cerr << "GPSService::read_gpgsa(sentence const&): " << __LINE__ << std::endl;
    parse_error pe("[$GPGSA] Could not convert string to number", p_nmea);
    throw pe;
  } catch (parse_error& ex) {
    std::cerr << "GPSService::read_gpgsa(sentence const&): " << __LINE__ << std::endl;
    parse_error pe("GPS Data Bad Format [$GPGSA] :: " + ex.message, p_nmea);
    throw pe;
  }
  std::cerr << "GPSService::read_gpgsa(sentence const&): " << __LINE__ << std::endl; //
}

void GPSService::read_gpgsv(sentence const& p_nmea) {
  std::cerr << "GPSService::read_gpgsv(sentence const&)\n";
  /*  -- EXAMPLE --
  $GPGSV,2,1,08,01,40,083,46,02,17,308,41,12,07,344,39,14,22,228,45*75


  $GPGSV,3,1,12,01,00,000,,02,00,000,,03,00,000,,04,00,000,*7C
  $GPGSV,3,2,12,05,00,000,,06,00,000,,07,00,000,,08,00,000,*77
  $GPGSV,3,3,12,09,00,000,,10,00,000,,11,00,000,,12,00,000,*71

  Where:
  GSV          Satellites in view
  [0] 2            Number of sentences for full data
  [1] 1            sentence 1 of 2
  [2] 08           Number of satellites in view

  [3] 01           satellite PRN number
  [4] 40           Elevation, degrees
  [5] 083          Azimuth, degrees
  [6] 46           SNR - higher is better
  [...]   for up to 4 satellites per sentence
  [17] *75          the checksum data, always begins with *
  */

  try {
    if (!p_nmea.is_checksum_ok()) {
      throw parse_error("Checksum is invalid!");
    }

    // can't do this check because the length varies depending on satellites...
    //if(nmea.parameters.size() < 18) {
    //  throw parse_error("GPS data is missing parameters.");
    //}

    // VISIBLE SATELLITES
    fix.visible_satellites = std::stoi(p_nmea.parameters[2]);
    if (this->fix.tracking_satellites == 0) {
      this->fix.visible_satellites = 0;      // if no satellites are tracking, then none are visible!
    }                        // Also NMEA defaults to 12 visible when chip powers on. Obviously not right.

    uint32_t total_pages = static_cast<uint32_t>(std::stoul(p_nmea.parameters[0]));

    //if this is the first page, then reset the almanac
    if (1 == std::stoul(p_nmea.parameters[1])) { // current page
      this->fix.almanac.clear();
    }

    this->fix.almanac.m_total_pages = total_pages;
    this->fix.almanac.m_visible_size = static_cast<uint32_t>(this->fix.visible_satellites);

    auto entriesInPage = (p_nmea.parameters.size() - 3) >> 2;  //first 3 are not satellite info
    //- entries come in 4-ples, and truncate, so used shift
    gps::satellite sat;
    for (unsigned long i = 0; i < entriesInPage; i++) {
      auto prop = 3 + i * 4;

      // PRN, ELEVATION, AZIMUTH, SNR
      sat.prn = static_cast<uint32_t>(std::stoul(p_nmea.parameters[prop]));
      sat.elevation = static_cast<uint32_t>(std::stoul(p_nmea.parameters[prop + 1]));
      sat.azimuth = static_cast<uint32_t>(std::stoul(p_nmea.parameters[prop + 2]));
      sat.snr = static_cast<uint32_t>(std::stoul(p_nmea.parameters[prop + 3]));

      fix.almanac.update_satellite(sat);
    }

    this->fix.almanac.m_processed_pages++;

    // 
    if (this->fix.visible_satellites == 0) {
      this->fix.almanac.clear();
    }

    //cout << "ALMANAC FINISHED page " << this->fix.almanac.m_processed_pages << " of " << this->fix.almanac.m_total_pages << endl;
    this->onUpdate();

  } catch (std::invalid_argument&) {
    parse_error pe("[$GPGSV] Could not convert string to number", p_nmea);
    throw pe;
  } catch (parse_error& ex) {
    parse_error pe("GPS Data Bad Format [$GPGSV] :: " + ex.message, p_nmea);
    throw pe;
  }
}

void GPSService::read_gprmc(sentence const& p_nmea) {
  std::cerr << "GPSService::read_gprmc(sentence const&)\n";
  /*  -- EXAMPLE ---
  $GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A
  $GPRMC,235957.025,V,,,,,,,070810,,,N*4B
  $GPRMC,061425.000,A,3346.2243,N,08423.4706,W,0.45,18.77,060914,,,A*47

  Where:
  RMC          Recommended Minimum sentence C
  [0] 123519       fix taken at 12:35:19 UTC
  [1] A            Status A=active or V=Void.
  [2-3] 4807.038,N   Latitude 48 deg 07.038' N
  [4-5] 01131.000,E  Longitude 11 deg 31.000' E
  [6] 022.4        Speed over the ground in knots
  [7] 084.4        Track angle in degrees True
  [8] 230394       Date - 23rd of March 1994
  [9-10] 003.1,W      Magnetic Variation
  [10] *6A          The checksum data, always begins with *
  // NMEA 2.3 includes another field after
  */

  try {
    if (!p_nmea.is_checksum_ok()) {
      throw parse_error("Checksum is invalid!");
    }

    if (p_nmea.parameters.size() < 11) {
      throw parse_error("GPS data is missing parameters.");
    }

    // TIMESTAMP
    this->fix.timestamp.set_time(std::stod(p_nmea.parameters[0]));

    std::string sll;
    std::string dir;
    // LAT
    sll = p_nmea.parameters[2];
    dir = p_nmea.parameters[3];
    if (!sll.empty()) {
      this->fix.latitude = convert_lat_lon_to_deg(sll, dir);
    }

    // LONG
    sll = p_nmea.parameters[4];
    dir = p_nmea.parameters[5];
    if (!sll.empty()) {
      this->fix.longitude = convert_lat_lon_to_deg(sll, dir);
    }

    // ACTIVE
    bool lockupdate = false;
    char status = 'V';
    if (!p_nmea.parameters[1].empty()) {
      status = p_nmea.parameters[1][0];
    }
    this->fix.status = status;
    if (status == 'V') {
      lockupdate = this->fix.set_lock(false);
    } else if (status == 'A') {
      lockupdate = this->fix.set_lock(true);
    } else {
      lockupdate =
          this->fix.set_lock(false);    //not A or V, so must be wrong... no lock
    }

    this->fix.speed = kts_to_kph(std::stod(p_nmea.parameters[6]));    // received as knots, convert to km/h
    this->fix.travel_angle = std::stod(p_nmea.parameters[7]);
    fix.timestamp.set_date(std::stoi(p_nmea.parameters[8]));

    //calling m_handlers
    if (lockupdate) {
      this->onLockStateChanged(this->fix.m_has_lock);
    }
    this->onUpdate();
  } catch (std::invalid_argument&) {
    parse_error pe("[$GPRMC] Could not convert string to number", p_nmea);
    throw pe;
  } catch (parse_error& ex) {
    parse_error pe("GPS Data Bad Format [$GPRMC] :: " + ex.message, p_nmea);
    throw pe;
  }
}

void GPSService::read_gpvtg(sentence const& p_nmea) {
  std::cerr << "GPSService::read_gpvtg(sentence const&)\n";
  /*
  $GPVTG,054.7,T,034.4,M,005.5,N,010.2,K*48

  where:
  VTG          Track made good and ground speed
  [0-1]  054.7,T      True track made good (degrees)
  [2-3]  034.4,M      Magnetic track made good
  [4-5]  005.5,N      Ground speed, knots
  [6-7]  010.2,K      Ground speed, Kilometers per hour
  [7]  *48          Checksum
  */

  try {
    if (!p_nmea.is_checksum_ok()) {
      throw parse_error("Checksum is invalid!");
    }

    if (p_nmea.parameters.size() < 8) {
      throw parse_error("GPS data is missing parameters.");
    }

    // SPEED
    // if empty, is converted to 0
    this->fix.speed = std::stod(p_nmea.parameters[6]);    //km/h

    this->onUpdate();
  } catch (std::invalid_argument&) {
    parse_error pe("[$GPVTG] Could not convert string to number", p_nmea);
    throw pe;
  } catch (parse_error& ex) {
    parse_error pe("GPS Data Bad Format [$GPVTG] :: " + ex.message, p_nmea);
    throw pe;
  }
}

} // namespace nmea

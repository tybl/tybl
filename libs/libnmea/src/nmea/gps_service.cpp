// License: The Unlicense (https://unlicense.org)
#include <nmea/gps_service.hpp>

#include <nmea/gps/satellite.hpp>
#include <vodka/parse_error.hpp>

#include <spdlog/spdlog.h>

#include <cmath>

namespace tybl::nmea {

// ------ Some helpers ----------
// Takes the NMEA lat/long format (dddmm.mmmm, [N/S,E/W]) and converts to degrees N,E only
static auto convert_lat_lon_to_deg(std::string const& p_lat_lon_str, std::string const& p_dir) -> double {

  double pd = std::stod(p_lat_lon_str);
  double deg = trunc(pd / 100); // get ddd from dddmm.mmmm
  double mins = pd - deg * 100;

  deg = deg + mins / 60.0;

  char hdg = 'x';
  if (!p_dir.empty()) {
    hdg = p_dir[0];
  }

  // everything should be N/E, so flip S,W
  if (hdg == 'S' || hdg == 'W') {
    deg *= -1.0;
  }

  return deg;
}

static auto kts_to_kph(double p_knots) -> double { return p_knots * 1.852; }

// ------------- GPSSERVICE CLASS -------------

gps_service::gps_service(sentence_parser& p_parser) {
  attach_to_parser(p_parser); // attach to parser in the GPS object
}

gps_service::~gps_service() = default;

void gps_service::attach_to_parser(sentence_parser& p_parser) {
  p_parser.set_sentence_handler("GNGGA", [this](const sentence& p_nmea) { read_gga(p_nmea); });
  p_parser.set_sentence_handler("GPGGA", [this](const sentence& p_nmea) { read_gga(p_nmea); });
  p_parser.set_sentence_handler("GLGSA", [this](const sentence& p_nmea) { read_gsa(p_nmea); });
  p_parser.set_sentence_handler("GPGSA", [this](const sentence& p_nmea) { read_gsa(p_nmea); });
  p_parser.set_sentence_handler("GLGSV", [this](const sentence& p_nmea) { read_gsv(p_nmea); });
  p_parser.set_sentence_handler("GPGSV", [this](const sentence& p_nmea) { read_gsv(p_nmea); });
  p_parser.set_sentence_handler("GNRMC", [this](const sentence& p_nmea) { read_rmc(p_nmea); });
  p_parser.set_sentence_handler("GPRMC", [this](const sentence& p_nmea) { read_rmc(p_nmea); });
  p_parser.set_sentence_handler("GNVTG", [this](const sentence& p_nmea) { read_vtg(p_nmea); });
  p_parser.set_sentence_handler("GPVTG", [this](const sentence& p_nmea) { read_vtg(p_nmea); });
}

void gps_service::read_gga(sentence const& p_nmea) {
  try {
    if (!p_nmea.is_checksum_ok()) {
      throw tybl::vodka::parse_error("Invalid checksum");
    }

    if (p_nmea.parameters.size() < 14) {
      throw tybl::vodka::parse_error("GPS data is missing parameters.");
    }

    // TIMESTAMP
    fix.m_timestamp.set_time(std::stod(p_nmea.parameters[0]));

    // LAT
    std::string sll = p_nmea.parameters[1];
    std::string dir = p_nmea.parameters[2];
    if (!sll.empty()) {
      fix.latitude = convert_lat_lon_to_deg(sll, dir);
    }

    // LONG
    sll = p_nmea.parameters[3];
    dir = p_nmea.parameters[4];
    if (!sll.empty()) {
      fix.longitude = convert_lat_lon_to_deg(sll, dir);
    }

    // FIX QUALITY
    bool lockupdate = false;
    fix.quality = static_cast<uint8_t>(std::stoul(p_nmea.parameters[5]));
    if (fix.quality == 0) {
      lockupdate = fix.set_lock(false);
    } else if (fix.quality == 1) {
      lockupdate = fix.set_lock(true);
    }

    // TRACKING SATELLITES
    fix.tracking_satellites = std::stoi(p_nmea.parameters[6]);
    if (fix.visible_satellites < fix.tracking_satellites) {
      fix.visible_satellites = fix.tracking_satellites; // the visible count is in another sentence.
    }

    // ALTITUDE
    if (!p_nmea.parameters[8].empty()) {
      fix.altitude = std::stod(p_nmea.parameters[8]);
    }

    // calling m_handlers
    if (lockupdate) {
      on_lock_state_changed(fix.m_has_lock);
    }
    on_update();
  } catch (std::invalid_argument const&) {
    throw tybl::vodka::parse_error("[$GPGGA] Could not convert string to a number");
  }
}

void gps_service::read_gsa(sentence const& p_nmea) {
  try {
    if (!p_nmea.is_checksum_ok()) {
      throw tybl::vodka::parse_error("Checksum is invalid!");
    }

    if (p_nmea.parameters.size() < 17) {
      throw tybl::vodka::parse_error("GPS data is missing parameters.");
    }

    // FIX TYPE
    bool lockupdate = false;
    auto fix_type = std::stoul(p_nmea.parameters[1]);
    fix.type = static_cast<uint8_t>(fix_type);
    if (fix_type == 1) {
      lockupdate = fix.set_lock(false);
    } else if (fix_type == 3) {
      lockupdate = fix.set_lock(true);
    }

    fix.dilution = p_nmea.parameters[14].empty() ? 0.0 : std::stod(p_nmea.parameters[14]);

    fix.horizontal_dilution = p_nmea.parameters[15].empty() ? 0.0 : std::stod(p_nmea.parameters[15]);

    fix.vertical_dilution = p_nmea.parameters[16].empty() ? 0.0 : std::stod(p_nmea.parameters[16]);

    // calling m_handlers
    if (lockupdate) {
      on_lock_state_changed(fix.m_has_lock);
    }
    on_update();
  } catch (std::invalid_argument const&) {
    throw tybl::vodka::parse_error("[$GPGSA] Could not convert string to number");
  }
}

void gps_service::read_gsv(sentence const& p_nmea) {
  try {
    if (!p_nmea.is_checksum_ok()) {
      throw tybl::vodka::parse_error("Checksum is invalid!");
    }

    // VISIBLE SATELLITES
    fix.visible_satellites = std::stoi(p_nmea.parameters[2]);
    if (fix.tracking_satellites == 0) {
      fix.visible_satellites = 0; // if no satellites are tracking, then none are visible!
    }                                   // Also NMEA defaults to 12 visible when chip powers on. Obviously not right.

    auto total_pages = static_cast<uint32_t>(std::stoul(p_nmea.parameters[0]));

    // if this is the first page, then reset the almanac
    if (1 == std::stoul(p_nmea.parameters[1])) { // current page
      fix.m_almanac.clear();
    }

    fix.m_almanac.m_total_pages = total_pages;
    fix.m_almanac.m_visible_size = static_cast<uint32_t>(fix.visible_satellites);

    auto entriesInPage = (p_nmea.parameters.size() - 3) >> 2; // first 3 are not satellite info
    //- entries come in 4-ples, and truncate, so used shift
    for (uint64_t i = 0; i < entriesInPage; i++) {
      auto prop = 3 + i * 4;
      try {
        tybl::nmea::gps::satellite sat{};
        // PRN, ELEVATION, AZIMUTH, SNR
        sat.prn = static_cast<uint32_t>(std::stoul(p_nmea.parameters[prop]));
        sat.elevation = static_cast<uint32_t>(std::stoul(p_nmea.parameters[prop + 1]));
        sat.azimuth = static_cast<uint32_t>(std::stoul(p_nmea.parameters[prop + 2]));
        sat.snr = static_cast<uint32_t>(std::stoul(p_nmea.parameters[prop + 3]));

        fix.m_almanac.update_satellite(sat);
      } catch (std::invalid_argument const& except) {
        spdlog::warn("Failed to convert GSV satellite because no conversion could be performed: {}", except.what());
      } catch (std::out_of_range const& except) {
        spdlog::warn("Failed to convert GSV satellite because it was out of range: {}", except.what());
      } catch (...) {
        spdlog::warn("Unknown exception caught while converting GSV satellite");
      }
    }

    fix.m_almanac.m_processed_pages++;

    if (fix.visible_satellites == 0) {
      fix.m_almanac.clear();
    }

    on_update();

  } catch (std::invalid_argument const&) {
    throw tybl::vodka::parse_error("[$GPGSV] Could not convert string to number");
  }
}

void gps_service::read_rmc(sentence const& p_nmea) {
  try {
    if (!p_nmea.is_checksum_ok()) {
      throw tybl::vodka::parse_error("Checksum is invalid!");
    }

    if (p_nmea.parameters.size() < 11) {
      throw tybl::vodka::parse_error("GPS data is missing parameters.");
    }

    // TIMESTAMP
    fix.m_timestamp.set_time(std::stod(p_nmea.parameters[0]));

    // LAT
    std::string sll = p_nmea.parameters[2];
    std::string dir = p_nmea.parameters[3];
    if (!sll.empty()) {
      fix.latitude = convert_lat_lon_to_deg(sll, dir);
    }

    // LONG
    sll = p_nmea.parameters[4];
    dir = p_nmea.parameters[5];
    if (!sll.empty()) {
      fix.longitude = convert_lat_lon_to_deg(sll, dir);
    }

    // ACTIVE
    bool lockupdate = false;
    char status = 'V';
    if (!p_nmea.parameters[1].empty()) {
      status = p_nmea.parameters[1][0];
    }
    fix.status = status;
    if (status == 'A') {
      lockupdate = fix.set_lock(true);
    }

    fix.speed = kts_to_kph(std::stod(p_nmea.parameters[6])); // received as knots, convert to km/h
    fix.travel_angle = std::stod(p_nmea.parameters[7]);
    fix.m_timestamp.set_date(std::stoi(p_nmea.parameters[8]));

    // calling m_handlers
    if (lockupdate) {
      on_lock_state_changed(fix.m_has_lock);
    }
    on_update();
  } catch (std::invalid_argument const&) {
    throw tybl::vodka::parse_error("[$GPRMC] Could not convert string to number");
  }
}

void gps_service::read_vtg(sentence const& p_nmea) {
  try {
    if (!p_nmea.is_checksum_ok()) {
      throw tybl::vodka::parse_error("Checksum is invalid!");
    }

    if (p_nmea.parameters.size() < 8) {
      throw tybl::vodka::parse_error("GPS data is missing parameters.");
    }

    // SPEED
    // if empty, is converted to 0
    fix.speed = std::stod(p_nmea.parameters[6]); // km/h

    on_update();
  } catch (std::invalid_argument const&) {
    throw tybl::vodka::parse_error("[$GPVTG] Could not convert string to number");
  }
}

} // namespace tybl::nmea

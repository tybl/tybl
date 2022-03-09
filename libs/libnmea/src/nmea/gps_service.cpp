// License: The Unlicense (https://unlicense.org)
#include <nmea/gps_service.hpp>

#include <nmea/gps/satellite.hpp>
#include <vodka/parse_error.hpp>

#include <spdlog/spdlog.h>

#include <charconv>
#include <cmath>

namespace tybl::nmea {

static auto convert_lat_lon_to_deg(std::string_view p_lat_lon_str, std::string_view p_dir) noexcept -> double {
  auto combined = 0.0;
  auto result = std::from_chars(p_lat_lon_str.begin(), p_lat_lon_str.end(), combined);
  auto degrees = std::trunc(combined / 100.0);
  if (result.ptr == p_lat_lon_str.end()) {
    degrees += (combined - degrees * 100.0) / 60.0;
    if (!p_dir.empty() && ('S' == p_dir.front() || 'W' == p_dir.front())) {
      degrees *= -1.0;
    }
  }
  return degrees;
}

static auto kts_to_kph(double p_knots) noexcept -> double { return p_knots * 1.85200; }

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
    double raw_time = 0;
    std::from_chars(p_nmea.parameters[0].begin(), p_nmea.parameters[0].end(), raw_time);
    fix.m_timestamp.set_time(raw_time);

    // LAT
    if (!p_nmea.parameters[1].empty()) {
      fix.latitude = convert_lat_lon_to_deg(p_nmea.parameters[1], p_nmea.parameters[2]);
    }

    // LONG
    if (!p_nmea.parameters[3].empty()) {
      fix.longitude = convert_lat_lon_to_deg(p_nmea.parameters[3], p_nmea.parameters[4]);
    }

    // FIX QUALITY
    bool lock_update = false;
    std::from_chars(p_nmea.parameters[5].begin(), p_nmea.parameters[5].end(), fix.quality);
    if (fix.quality == 0) {
      lock_update = fix.set_lock(false);
    } else if (fix.quality == 1) {
      lock_update = fix.set_lock(true);
    }

    // TRACKING SATELLITES
    std::from_chars(p_nmea.parameters[6].begin(), p_nmea.parameters[6].end(), fix.tracking_satellites);
    if (fix.visible_satellites < fix.tracking_satellites) {
      fix.visible_satellites = fix.tracking_satellites; // the visible count is in another sentence.
    }

    // ALTITUDE
    std::from_chars(p_nmea.parameters[8].begin(), p_nmea.parameters[8].end(), fix.altitude);

    // calling m_handlers
    if (lock_update) {
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
    std::from_chars(p_nmea.parameters[1].begin(), p_nmea.parameters[1].end(), fix.type);
    if (fix.type == 1) {
      lockupdate = fix.set_lock(false);
    } else if (fix.type == 3) {
      lockupdate = fix.set_lock(true);
    }

    std::from_chars(p_nmea.parameters[14].begin(), p_nmea.parameters[14].end(), fix.dilution);

    std::from_chars(p_nmea.parameters[15].begin(), p_nmea.parameters[15].end(), fix.horizontal_dilution);

    std::from_chars(p_nmea.parameters[16].begin(), p_nmea.parameters[16].end(), fix.vertical_dilution);

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
    std::from_chars(p_nmea.parameters[2].begin(), p_nmea.parameters[2].end(), fix.visible_satellites);
    if (fix.tracking_satellites == 0) {
      fix.visible_satellites = 0; // if no satellites are tracking, then none are visible!
    }                             // Also NMEA defaults to 12 visible when chip powers on. Obviously not right.

    uint32_t total_pages = 0;
    std::from_chars(p_nmea.parameters[0].begin(), p_nmea.parameters[0].end(), total_pages);

    // if this is the first page, then reset the almanac
    int page_index = 0;
    std::from_chars(p_nmea.parameters[1].begin(), p_nmea.parameters[1].end(), page_index);
    if (1 == page_index) { // current page
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
        std::from_chars(p_nmea.parameters[prop].begin(), p_nmea.parameters[prop].end(), sat.prn);
        std::from_chars(p_nmea.parameters[prop + 1].begin(), p_nmea.parameters[prop + 1].end(), sat.elevation);
        std::from_chars(p_nmea.parameters[prop + 2].begin(), p_nmea.parameters[prop + 2].end(), sat.azimuth);
        std::from_chars(p_nmea.parameters[prop + 3].begin(), p_nmea.parameters[prop + 3].end(), sat.snr);

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
    double raw_time = 0;
    std::from_chars(p_nmea.parameters[0].begin(), p_nmea.parameters[0].end(), raw_time);
    fix.m_timestamp.set_time(raw_time);

    // LAT
    if (!p_nmea.parameters[2].empty()) {
      fix.latitude = convert_lat_lon_to_deg(p_nmea.parameters[2], p_nmea.parameters[3]);
    }

    // LONG
    if (!p_nmea.parameters[4].empty()) {
      fix.longitude = convert_lat_lon_to_deg(p_nmea.parameters[4], p_nmea.parameters[5]);
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

    double speed_kts = 0.0;
    std::from_chars(p_nmea.parameters[6].begin(), p_nmea.parameters[6].end(), speed_kts);
    fix.speed = kts_to_kph(speed_kts);
    std::from_chars(p_nmea.parameters[7].begin(), p_nmea.parameters[7].end(), fix.travel_angle);
    int raw_date = 0;
    std::from_chars(p_nmea.parameters[8].begin(), p_nmea.parameters[8].end(), raw_date);
    fix.m_timestamp.set_date(raw_date);

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
    std::from_chars(p_nmea.parameters[6].begin(), p_nmea.parameters[6].end(), fix.speed);
    // fix.speed = std::stod(p_nmea.parameters[6]); // km/h

    on_update();
  } catch (std::invalid_argument const&) {
    throw tybl::vodka::parse_error("[$GPVTG] Could not convert string to number");
  }
}

} // namespace tybl::nmea

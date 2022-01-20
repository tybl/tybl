// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_GPSSERVICE_HPP
#define TYBL_NMEA_GPSSERVICE_HPP

#include "gps/fix.hpp"
#include "nmea/Event.hpp"
#include "nmea/Parser.hpp"

#include <chrono>
#include <functional>
#include <string>

namespace nmea {

class GPSService {
  void read_psrf150(sentence const& p_nmea);
  void read_gpgga(sentence const& p_nmea);
  void read_gpgsa(sentence const& p_nmea);
  void read_gpgsv(sentence const& p_nmea);
  void read_gprmc(sentence const& p_nmea);
  void read_gpvtg(sentence const& p_nmea);

public:
  gps::fix fix;

  GPSService(Parser& p_parser);

  virtual ~GPSService();

  Event<void(bool)> on_lock_state_changed; // user assignable handler, called whenever lock changes

  Event<void()> on_update; // user assignable handler, called whenever fix changes

  void attach_to_parser(Parser& p_parser); // will attach to this parser's nmea sentence events

}; // class GPSService

} // namespace nmea

#endif // TYBL_NMEA_GPSSERVICE_HPP
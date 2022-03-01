// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_GPSSERVICE_HPP
#define TYBL_NMEA_GPSSERVICE_HPP

#include <nmea/event.hpp>
#include <nmea/gps/fix.hpp>
#include <nmea/sentence_parser.hpp>

#include <chrono>
#include <functional>
#include <string>

namespace tybl::nmea {

class gps_service {
  static void read_psrf150(sentence const& p_nmea);
  void read_gga(sentence const& p_nmea);
  void read_gsa(sentence const& p_nmea);
  void read_gsv(sentence const& p_nmea);
  void read_rmc(sentence const& p_nmea);
  void read_vtg(sentence const& p_nmea);

public:
  gps::fix fix;

  explicit gps_service(sentence_parser& p_parser);

  virtual ~gps_service();

  Event<void(bool)> on_lock_state_changed; // user assignable handler, called whenever lock changes

  Event<void()> on_update; // user assignable handler, called whenever fix changes

  void attach_to_parser(sentence_parser& p_parser); // will attach to this parser's nmea sentence events

}; // class gps_service

} // namespace tybl::nmea

#endif // TYBL_NMEA_GPSSERVICE_HPP

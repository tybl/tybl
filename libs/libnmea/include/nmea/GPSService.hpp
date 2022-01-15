#pragma once

#include "gps/fix.hpp"
#include "nmea/Parser.hpp"
#include "nmea/Event.hpp"

#include <chrono>
#include <functional>
#include <string>

namespace nmea {

class GPSService {
  void read_psrf150(sentence const& nmea);
  void read_gpgga  (sentence const& nmea);
  void read_gpgsa  (sentence const& nmea);
  void read_gpgsv  (sentence const& nmea);
  void read_gprmc  (sentence const& nmea);
  void read_gpvtg  (sentence const& nmea);
public:

  gps::fix fix;

  GPSService(Parser& parser);

  virtual ~GPSService();

  Event<void(bool)> onLockStateChanged; // user assignable handler, called whenever lock changes

  Event<void()> onUpdate; // user assignable handler, called whenever fix changes

  void attach_to_parser(Parser& parser); // will attach to this parser's nmea sentence events

}; // class GPSService

} // namespace nmea

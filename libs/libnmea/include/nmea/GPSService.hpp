#pragma once

#include "gps/Fix.hpp"
#include "nmea/Parser.hpp"
#include "nmea/Event.hpp"

#include <chrono>
#include <functional>
#include <string>

namespace nmea {

class GPSService {
  void read_psrf150(Sentence const& nmea);
  void read_gpgga  (Sentence const& nmea);
  void read_gpgsa  (Sentence const& nmea);
  void read_gpgsv  (Sentence const& nmea);
  void read_gprmc  (Sentence const& nmea);
  void read_gpvtg  (Sentence const& nmea);
public:

  gps::Fix fix;

  GPSService(Parser& parser);

  virtual ~GPSService();

  Event<void(bool)> onLockStateChanged; // user assignable handler, called whenever lock changes

  Event<void()> onUpdate; // user assignable handler, called whenever fix changes

  void attach_to_parser(Parser& parser); // will attach to this parser's nmea sentence events

}; // class GPSService

} // namespace nmea

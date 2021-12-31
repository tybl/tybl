#pragma once

#include "gps/Fix.hpp"
#include "nmea/Parser.hpp"
#include "nmea/Event.hpp"

#include <chrono>
#include <functional>
#include <string>

namespace nmea {

class GPSService {
  void read_PSRF150(Sentence const& nmea);
  void read_GPGGA  (Sentence const& nmea);
  void read_GPGSA  (Sentence const& nmea);
  void read_GPGSV  (Sentence const& nmea);
  void read_GPRMC  (Sentence const& nmea);
  void read_GPVTG  (Sentence const& nmea);
public:

  gps::Fix fix;

  GPSService(Parser& parser);

  virtual ~GPSService();

  Event<void(bool)> onLockStateChanged; // user assignable handler, called whenever lock changes

  Event<void()> onUpdate; // user assignable handler, called whenever fix changes

  void attachToParser(Parser& parser); // will attach to this parser's nmea sentence events

}; // class GPSService

} // namespace nmea

// License: The Unlicense (https://unlicense.org)
#include <nmea/gps_service.hpp>
#include <nmea/byte_parser.hpp>

#include <doctest/doctest.h>

#include <string_view>

TEST_CASE("nmea::parse") {
  tybl::nmea::byte_parser parser;
  // Q: Why does the Parser object get injected into the gps_service object?
  // A: Because the gps_service needs to register for which NMEA sentences it
  //    wants to observe. There are several of them, so it is easier for the
  //    gps_service to do it, since it knows which ones it cares about.
  tybl::nmea::gps_service gps(parser);

  // Let's make sure gps_service is initialized to a known state
  CHECK(0.0 == gps.fix.altitude);
  CHECK(0.0 == gps.fix.dilution);
  CHECK(0.0 == gps.fix.horizontal_dilution);
  CHECK(0.0 == gps.fix.latitude);
  CHECK(0.0 == gps.fix.longitude);
  CHECK(0 == gps.fix.quality);
  CHECK(0.0 == gps.fix.speed);
  CHECK('V' == gps.fix.status); // This seems wrong
  CHECK(1 == gps.fix.m_timestamp.day);
  CHECK(0 == gps.fix.m_timestamp.hour);
  CHECK(0 == gps.fix.m_timestamp.min);
  CHECK(1 == gps.fix.m_timestamp.month);
  CHECK(1970 == gps.fix.m_timestamp.year);
  CHECK(0.0 == gps.fix.m_timestamp.sec);
  CHECK(0 == gps.fix.tracking_satellites);
  CHECK(0.0 == gps.fix.travel_angle);
  CHECK(1 == gps.fix.type);
  CHECK(0.0 == gps.fix.vertical_dilution);
  CHECK(0 == gps.fix.visible_satellites);

  std::string_view input {
    "$GNGGA,171250.000,4014.9259,N,07938.4143,W,2,13,0.72,325.1,M,-33.0,M,,*4D\n"
  };

  parser.read_buffer(input);

  CHECK(doctest::Approx(325.1) == gps.fix.altitude);
  CHECK(0.0 == gps.fix.dilution); // Unchanged
  CHECK(0.0 == gps.fix.horizontal_dilution); // Unchanged
  CHECK(doctest::Approx(40.249016667) == gps.fix.latitude);
  CHECK(doctest::Approx(-79.640411667) == gps.fix.longitude);
  CHECK(2 == gps.fix.quality);
  CHECK(0.0 == gps.fix.speed); // Unchanged
  CHECK('V' == gps.fix.status);
  CHECK(1 == gps.fix.m_timestamp.day); // Unchanged
  CHECK(17 == gps.fix.m_timestamp.hour);
  CHECK(12 == gps.fix.m_timestamp.min);
  CHECK(1 == gps.fix.m_timestamp.month); // Unchanged
  CHECK(1970 == gps.fix.m_timestamp.year); // Unchanged
  CHECK(doctest::Approx(50.0) == gps.fix.m_timestamp.sec);
  CHECK(13 == gps.fix.tracking_satellites);
  CHECK(0.0 == gps.fix.travel_angle); // Unchanged
  CHECK(1 == gps.fix.type); // Unchanged
  CHECK(0.0 == gps.fix.vertical_dilution); // Unchanged
  CHECK(13 == gps.fix.visible_satellites);

  // Q: What happens if we run the same string through the parser?
  // A: Doesn't appear to change anything after the first
  parser.read_buffer(input);

  CHECK(doctest::Approx(325.1) == gps.fix.altitude); // Unchanged
  CHECK(0.0 == gps.fix.dilution); // Unchanged
  CHECK(0.0 == gps.fix.horizontal_dilution); // Unchanged
  CHECK(doctest::Approx(40.249016667) == gps.fix.latitude); // Unchanged
  CHECK(doctest::Approx(-79.640411667) == gps.fix.longitude); // Unchanged
  CHECK(2 == gps.fix.quality); // Unchanged
  CHECK(0.0 == gps.fix.speed); // Unchanged
  CHECK('V' == gps.fix.status); // Unchanged
  CHECK(1 == gps.fix.m_timestamp.day); // Unchanged
  CHECK(17 == gps.fix.m_timestamp.hour); // Unchanged
  CHECK(12 == gps.fix.m_timestamp.min); // Unchanged
  CHECK(1 == gps.fix.m_timestamp.month); // Unchanged
  CHECK(1970 == gps.fix.m_timestamp.year); // Unchanged
  CHECK(doctest::Approx(50.0) == gps.fix.m_timestamp.sec); // Unchanged
  CHECK(13 == gps.fix.tracking_satellites); // Unchanged
  CHECK(0.0 == gps.fix.travel_angle); // Unchanged
  CHECK(1 == gps.fix.type); // Unchanged
  CHECK(0.0 == gps.fix.vertical_dilution); // Unchanged
  CHECK(13 == gps.fix.visible_satellites); // Unchanged
}

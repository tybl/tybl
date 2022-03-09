// License: The Unlicense (https://unlicense.org)
#include <nmea/byte_parser.hpp>
#include <nmea/gps_service.hpp>

#include <doctest/doctest.h>

#include <string_view>

TEST_CASE("read_gga") {
  tybl::nmea::byte_parser parser;
  tybl::nmea::gps_service gps(parser);

  std::string_view input{"$GNGGA,155644.000,4000.6896,N,07836.5715,W,2,11,0.93,369.5,M,-33.1,M,,*42\r\n"};
  parser.read_buffer(input);

  CHECK(15 == gps.fix.m_timestamp.hour());
  CHECK(56 == gps.fix.m_timestamp.min());
  CHECK(doctest::Approx(44.0) == gps.fix.m_timestamp.sec());
  CHECK(doctest::Approx(40.011493333) == gps.fix.latitude);
  CHECK(doctest::Approx(-78.609525) == gps.fix.longitude);
  CHECK(2 == gps.fix.quality);
  CHECK(11 == gps.fix.visible_satellites);
  // TODO(tybl): CHECK(doctest::Approx(0.93) == gps.fix.horizontal_dilution);
  CHECK(doctest::Approx(369.5) == gps.fix.altitude);
  // TODO(tybl): Height of geoid about WGS84
  // No time since last DGPS update
  // No DGPS reference station id
}

TEST_CASE("read_gsa") {
  // Satellites active
  tybl::nmea::byte_parser parser;
  tybl::nmea::gps_service gps(parser);

  std::string_view input1{"$GPGSA,A,3,21,32,23,31,01,25,10,,,,,,1.24,0.93,0.82*03\r\n"};
  parser.read_buffer(input1);

  // TODO(tybl): Active satellites
  CHECK(doctest::Approx(1.24) == gps.fix.dilution);
  CHECK(doctest::Approx(0.93) == gps.fix.horizontal_dilution);
  CHECK(doctest::Approx(0.82) == gps.fix.vertical_dilution);
  CHECK(3 == gps.fix.type);
}

TEST_CASE("read_gsv") {
  // Satellites in view
  tybl::nmea::byte_parser parser;
  tybl::nmea::gps_service gps(parser);

  std::string_view input{"$GNGGA,155644.000,4000.6896,N,07836.5715,W,2,11,0.93,369.5,M,-33.1,M,,*42\r\n"};
  std::string_view input1{"$GPGSV,3,1,10,32,71,017,32,31,55,232,33,10,48,155,33,25,43,095,35*7D\r\n"};
  std::string_view input2{"$GPGSV,3,2,10,51,35,220,36,12,26,056,,21,22,280,30,01,19,305,31*7D\r\n"};
  std::string_view input3{"$GPGSV,3,3,10,23,15,147,33,26,06,187,*73\r\n"};
  parser.read_buffer(input);
  parser.read_buffer(input1);
  parser.read_buffer(input2);
  parser.read_buffer(input3);

  CHECK(10 == gps.fix.visible_satellites);
  CHECK(11 == gps.fix.tracking_satellites);
  CHECK(32 == gps.fix.m_almanac.satellites[0].prn);
  CHECK(doctest::Approx(71) == gps.fix.m_almanac.satellites[0].elevation);
  CHECK(doctest::Approx(17) == gps.fix.m_almanac.satellites[0].azimuth);
  CHECK(doctest::Approx(32) == gps.fix.m_almanac.satellites[0].snr);
  CHECK(31 == gps.fix.m_almanac.satellites[1].prn);
  CHECK(doctest::Approx(55) == gps.fix.m_almanac.satellites[1].elevation);
  CHECK(doctest::Approx(232) == gps.fix.m_almanac.satellites[1].azimuth);
  CHECK(doctest::Approx(33) == gps.fix.m_almanac.satellites[1].snr);
  CHECK(10 == gps.fix.m_almanac.satellites[2].prn);
  CHECK(doctest::Approx(48) == gps.fix.m_almanac.satellites[2].elevation);
  CHECK(doctest::Approx(155) == gps.fix.m_almanac.satellites[2].azimuth);
  CHECK(doctest::Approx(33) == gps.fix.m_almanac.satellites[2].snr);
  CHECK(25 == gps.fix.m_almanac.satellites[3].prn);
  CHECK(doctest::Approx(43) == gps.fix.m_almanac.satellites[3].elevation);
  CHECK(doctest::Approx(95) == gps.fix.m_almanac.satellites[3].azimuth);
  CHECK(doctest::Approx(35) == gps.fix.m_almanac.satellites[3].snr);
  CHECK(51 == gps.fix.m_almanac.satellites[4].prn);
  CHECK(doctest::Approx(35) == gps.fix.m_almanac.satellites[4].elevation);
  CHECK(doctest::Approx(220) == gps.fix.m_almanac.satellites[4].azimuth);
  CHECK(doctest::Approx(36) == gps.fix.m_almanac.satellites[4].snr);
  CHECK(12 == gps.fix.m_almanac.satellites[5].prn);
  CHECK(doctest::Approx(26) == gps.fix.m_almanac.satellites[5].elevation);
  CHECK(doctest::Approx(56) == gps.fix.m_almanac.satellites[5].azimuth);
  CHECK(doctest::Approx(0) == gps.fix.m_almanac.satellites[5].snr);
  CHECK(21 == gps.fix.m_almanac.satellites[6].prn);
  CHECK(doctest::Approx(22) == gps.fix.m_almanac.satellites[6].elevation);
  CHECK(doctest::Approx(280) == gps.fix.m_almanac.satellites[6].azimuth);
  CHECK(doctest::Approx(30) == gps.fix.m_almanac.satellites[6].snr);
  CHECK(1 == gps.fix.m_almanac.satellites[7].prn);
  CHECK(doctest::Approx(19) == gps.fix.m_almanac.satellites[7].elevation);
  CHECK(doctest::Approx(305) == gps.fix.m_almanac.satellites[7].azimuth);
  CHECK(doctest::Approx(31) == gps.fix.m_almanac.satellites[7].snr);
  CHECK(23 == gps.fix.m_almanac.satellites[8].prn);
  CHECK(doctest::Approx(15) == gps.fix.m_almanac.satellites[8].elevation);
  CHECK(doctest::Approx(147) == gps.fix.m_almanac.satellites[8].azimuth);
  CHECK(doctest::Approx(33) == gps.fix.m_almanac.satellites[8].snr);
  CHECK(26 == gps.fix.m_almanac.satellites[9].prn);
  CHECK(doctest::Approx(6) == gps.fix.m_almanac.satellites[9].elevation);
  CHECK(doctest::Approx(187) == gps.fix.m_almanac.satellites[9].azimuth);
  CHECK(doctest::Approx(0) == gps.fix.m_almanac.satellites[9].snr);
}

TEST_CASE("read_rmc") {
  tybl::nmea::byte_parser parser;
  tybl::nmea::gps_service gps(parser);

  std::string_view input{"$GNRMC,155644.000,A,4000.6896,N,07836.5715,W,55.03,340.39,251221,,,D*50\r\n"};
  parser.read_buffer(input);

  CHECK(15 == gps.fix.m_timestamp.hour());
  CHECK(56 == gps.fix.m_timestamp.min());
  CHECK(doctest::Approx(44.0) == gps.fix.m_timestamp.sec());
  CHECK('A' == gps.fix.status); // This seems wrong
  CHECK(doctest::Approx(40.011493333) == gps.fix.latitude);
  CHECK(doctest::Approx(-78.609525) == gps.fix.longitude);
  CHECK(doctest::Approx(101.91556) == gps.fix.speed);
  CHECK(doctest::Approx(340.39) == gps.fix.travel_angle);
  CHECK(25 == gps.fix.m_timestamp.day());
  CHECK(12 == gps.fix.m_timestamp.month());
  CHECK(2021 == gps.fix.m_timestamp.year());
}

TEST_CASE("read_vtg") {
  tybl::nmea::byte_parser parser;
  tybl::nmea::gps_service gps(parser);

  std::string_view input{"$GNVTG,340.39,T,,M,55.03,N,101.97,K,D*16\r\n"};
  parser.read_buffer(input);

  // TODO(tybl): Measured heading (true north)
  // TODO(tybl): Measured heading (magnetic north)?
  // TODO(tybl): Speed (knots)?
  CHECK(doctest::Approx(101.97) == gps.fix.speed);
  // TODO(tybl): Mode
}

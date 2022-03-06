// License: The Unlicense (https://unlicense.org)
#include <nmea/gps_service.hpp>
#include <nmea/sentence_parser.hpp>

#include <doctest/doctest.h>

TEST_CASE("set_sentence_handler replacement") {
  tybl::nmea::sentence_parser parser;
  bool was_a_run = false;
  bool was_b_run = false;
  auto lambda_a = [&was_a_run](tybl::nmea::sentence const&){ was_a_run = true; };
  auto lambda_b = [&was_b_run](tybl::nmea::sentence const&){ was_b_run = true; };
  parser.set_sentence_handler("A",lambda_a);
  CHECK(!was_a_run);
  CHECK(!was_b_run);
  parser.read_sentence("$A\r\n");
  CHECK(was_a_run);
  CHECK(!was_b_run);
  was_a_run = false;
  parser.set_sentence_handler("A",lambda_b);
  CHECK(!was_a_run);
  CHECK(!was_b_run);
  parser.read_sentence("$A\r\n");
  CHECK(!was_a_run);
  CHECK(was_b_run);
}
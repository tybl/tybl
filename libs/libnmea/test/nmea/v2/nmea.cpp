// License: The Unlicense (https://unlicense.org)

#include <nmea/v2/latest_state.hpp>
#include <nmea/v2/parser.hpp>

#include <doctest/doctest.h>

TEST_CASE("New code") {
  latest_state state;
  parser p(state);
  p.parse("$GNRMC,020219.000,A,3924.6965,N,07657.7015,W,0.65,189.45,140322,,,D*6B\r\n");
  CHECK(state.longitude() == -7657.7015F);
  CHECK(state.latitude() == 3924.6965F);
}

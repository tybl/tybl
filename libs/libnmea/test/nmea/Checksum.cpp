// License: The Unlicense (https://unlicense.org)
#include <nmea/Checksum.hpp>

#include <doctest/doctest.h>

#include <string_view>

constexpr auto operator "" _chk(const char* p_string, size_t p_count) -> tybl::nmea::Checksum {
  std::string_view input(p_string, p_count);
  tybl::nmea::Checksum result{};
  for (auto character : input) {
    result += static_cast<std::byte>(character);
  }
  return result;
}

TEST_CASE("tybl::nmea::checksum") {
  auto chksm1 = "PFEC,GPint,RMC05"_chk;
  CHECK(0x2D == static_cast<uint8_t>(chksm1.value));

  auto chksm2 = "GPGGA,092750.000,5321.6802,N,00630.3372,W,1,8,1.03,61.7,M,55.2,M,,"_chk;
  CHECK(0x76 == static_cast<uint8_t>(chksm2.value));
}

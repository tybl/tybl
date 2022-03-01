// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_CHECKSUM_HPP
#define TYBL_NMEA_CHECKSUM_HPP

#include <cstddef>

namespace tybl::nmea {

struct Checksum {

  std::byte value;

  constexpr auto operator += (std::byte p_value) noexcept -> std::byte {
    return value ^= p_value;
  }

}; // struct Checksum

} // namespace tybl::nmea

#endif // TYBL_NMEA_CHECKSUM_HPP

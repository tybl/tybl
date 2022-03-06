// License: The Unlicense (https://unlicense.org)
#include "nmea/sentence.hpp"

namespace tybl::nmea {

auto sentence::valid() const -> bool { return m_is_valid; }

auto sentence::is_checksum_ok() const -> bool {
  return m_is_checksum_calculated && (m_parsed_checksum == m_calculated_checksum);
}

} // namespace tybl::nmea
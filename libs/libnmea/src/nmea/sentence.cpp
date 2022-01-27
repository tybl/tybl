// License: The Unlicense (https://unlicense.org)
#include "nmea/sentence.hpp"

namespace nmea {

sentence::sentence()
  : m_is_valid(false)
  , m_is_checksum_calculated(false)
  , m_parsed_checksum(0)
  , m_calculated_checksum(0) {}

sentence::~sentence() = default;

bool sentence::valid() const { return m_is_valid; }

bool sentence::is_checksum_ok() const {
  return (m_is_checksum_calculated) && (m_parsed_checksum == m_calculated_checksum);
}

} // namespace nmea

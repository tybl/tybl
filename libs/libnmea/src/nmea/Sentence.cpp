#include "nmea/Sentence.hpp"

namespace nmea {

Sentence::Sentence()
  : isvalid(false)
  , m_is_checksum_calculated(false)
  , m_parsed_checksum(0)
  , m_calculated_checksum(0)
{ }

Sentence::~Sentence() = default;

bool Sentence::valid() const {
  return isvalid;
}

bool Sentence::checksumOK() const {
  return (m_is_checksum_calculated) && (m_parsed_checksum == m_calculated_checksum);
}

} // namespace nmea

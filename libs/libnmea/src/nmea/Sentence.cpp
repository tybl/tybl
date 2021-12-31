#include "nmea/Sentence.hpp"

namespace nmea {

Sentence::Sentence()
  : isvalid(false)
  , checksumIsCalculated(false)
  , calculatedChecksum(0)
  , parsedChecksum(0)
{ }

Sentence::~Sentence() = default;

bool Sentence::valid() const {
  return isvalid;
}

bool Sentence::checksumOK() const {
  return (checksumIsCalculated) && (parsedChecksum == calculatedChecksum);
}

} // namespace nmea

#pragma once

#include <string>
#include <vector>

namespace nmea {

class Parser;

class Sentence {
  friend Parser;
private:
  bool isvalid;
public:
  std::string text;      //whole plaintext of the received command
  std::string name;      //name of the command
  std::vector<std::string> parameters;  //list of parameters from the command
  std::string checksum;
  bool checksumIsCalculated;
  uint8_t parsedChecksum;
  uint8_t calculatedChecksum;

  enum MessageID {    // These ID's are according to NMEA standard.
    Unknown = -1,
    GGA = 0,
    GLL = 1,
    GSA = 2,
    GSV = 3,
    RMC = 4,
    VTG = 5,    // notice missing 6,7
    ZDA = 8
  };
public:
  Sentence();
  virtual ~Sentence();

  bool checksumOK() const;
  bool valid() const;

}; // class Sentence

} // namespace nmea

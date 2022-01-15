// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_QUERYRATE_HPP
#define TYBL_NMEA_QUERYRATE_HPP

#include "nmea/command.hpp"

namespace nmea {

//  $PSRF103,00,01,00,01*25
/*
* Table 2-9 Query/Rate Control Data Format
Name    Example    Unit Description
Message m_id  $PSRF103  PSRF103 protocol header
Msg      00       See Table 2-10
Mode    01       0=SetRate, 1=Query
Rate    00       sec Output—off=0, max=255
CksumEnable 01       0=Disable Checksum, 1=Enable Checksum
Checksum  *25
<CR> <LF> End of message termination
*/
/*
* Table 2-10 Messages
value Description
0 GGA
1 GLL
2 GSA
3 GSV
4 RMC
5 VTG
6 MSS (If internal beacon is supported)
7 Not defined
8 ZDA (if 1PPS output is supported)
9 Not defined
*/
struct query_rate : public command {
  // data fields that will be stringed.

  enum QueryRateMode {
    SETRATE = 0,
    QUERY = 1
  };

  sentence::MessageID messageID;
  QueryRateMode mode;
  int rate;
  int checksumEnable;
public:
  query_rate()
    : command("PSRF103")
  {
    messageID = sentence::Unknown;
    mode = QueryRateMode::SETRATE;
    rate = 0;
    checksumEnable = 1;
  };

  std::string to_string() override;

}; // struct query_rate

} // namespace nmea

#endif // TYBL_NMEA_QUERYRATE_HPP
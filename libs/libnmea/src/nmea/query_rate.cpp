// License: The Unlicense (https://unlicense.org)
#include "nmea/query_rate.hpp"

#include <iomanip>
#include <sstream>

namespace nmea {

  //  $PSRF103,00,01,00,01*25
  /*
   * Table 2-9 Query/Rate Control Data Format
    Name Example Unit Description
    Message ID $PSRF103 PSRF103 protocol header
    Msg 00     See Table 2-10
    Mode 01     0=SetRate, 1=Query
    Rate 00     sec Output—off=0, max=255
    CksumEnable 01   0=Disable Checksum, 1=Enable Checksum
    Checksum *25
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
// Data Members:
//   int messageID;
//   int mode;
//   int rate;
//   int checksumEnable;
// Creates a valid NMEA $PSRF103 command sentence.
std::string query_rate::to_string(){
  std::stringstream ss;

  ss << std::setfill('0') << std::setw(2) << messageID << ","
     << std::setfill('0') << std::setw(2) << mode << ","
     << std::setfill('0') << std::setw(2) << rate << ","
     << std::setfill('0') << std::setw(2) << checksumEnable;
  // TODO(tybl): Does `message` need to persist if it is just passed as a copy?
  std::string message = ss.str();

  return command::add_checksum(message);
}

} // namespace nmea

// License: The Unlicense (https://unlicense.org)
#include "nmea/serial_configuration.hpp"

#include <sstream>

namespace nmea {

    /*
    // $PSRF100,0,9600,8,1,0*0C

    Table 2-4 Set Serial Port Data Format
     Name    Example    Unit Description
     Message m_id  $PSRF100  PSRF100 protocol header
     Protocol  0       0=SiRF binary, 1=NMEA
     Baud     9600     1200, 2400, 4800, 9600, 19200, 38400, 57600, and 115200
     DataBits  8       8,71

     StopBits  1       0,1    1. SiRF protocol is only valid for 8 data bits, 1stop bit, and no parity.
     Parity    0       0=None, 1=Odd, 2=Even
     Checksum  *0C
     <CR> <LF> End of message termination
    */
std::string serial_configuration::to_string() {
  std::stringstream ss;

  ss << "1," << baud << "," << databits << "," << stopbits << "," << parity;
  std::string message = ss.str();

  return command::add_checksum(message);
}

} // namespace nmea

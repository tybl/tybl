// License: The Unlicense (https://unlicense.org)
#pragma once

#include "nmea/command.hpp"

namespace nmea {

/*
// $PSRF100,0,9600,8,1,0*0C

Table 2-4 Set Serial Port Data Format
Name    Example    Unit Description
Message ID  $PSRF100  PSRF100 protocol header
Protocol  0       0=SiRF binary, 1=NMEA
Baud     9600     1200, 2400, 4800, 9600, 19200, 38400, 57600, and 115200
DataBits  8       8,71

StopBits  1       0,1    1. SiRF protocol is only valid for 8 data bits, 1stop bit, and no parity.
Parity    0       0=None, 1=Odd, 2=Even
Checksum  *0C
<CR> <LF> End of message termination
*/
struct serial_configuration : public command {
  int32_t baud;       //4800, 9600, 19200, 38400
  int32_t databits;  //7, 8 Databits
  int32_t stopbits;  //0, 1 Stopbits
  int32_t parity;    //0=none, 1=odd, 2=even Parity
public:
  serial_configuration()
    : command("PSRF100")
  {
    baud = 4800;
    databits = 8;
    stopbits = 1;
    parity = 0;
  }

  std::string to_string() override;

}; // struct serial_configuration

} // namespace nmea

// License: The Unlicense (https://unlicense.org)
#include <nmea/nmea.hpp>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(uint8_t const* p_data, size_t p_size)
{
  tybl::nmea::byte_parser parser;
  // Q: Why does the Parser object get injected into the gps_service object?
  // A: Because the gps_service needs to register for which NMEA sentences it
  //    wants to observe. There are several of them, so it is easier for the
  //    gps_service to do it, since it knows which ones it cares about.
  tybl::nmea::gps_service gps(parser);

  parser.read_buffer(std::string_view(reinterpret_cast<char const*>(p_data), p_size));

  return 0;
}

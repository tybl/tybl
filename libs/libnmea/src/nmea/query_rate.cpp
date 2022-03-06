// License: The Unlicense (https://unlicense.org)
#include "nmea/query_rate.hpp"

#include <iomanip>
#include <sstream>

namespace tybl::nmea {

auto query_rate::to_string() -> std::string {
  std::stringstream ss;

  ss << std::setfill('0') << std::setw(2) << message_id << "," << std::setfill('0') << std::setw(2) << mode << ","
     << std::setfill('0') << std::setw(2) << rate << "," << std::setfill('0') << std::setw(2) << checksum_enable;
  // TODO(tybl): Does `message` need to persist if it is just passed as a copy?
  std::string message = ss.str();

  return command::add_checksum(message);
}

} // namespace tybl::nmea
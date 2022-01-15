// License: The Unlicense (https://unlicense.org)
#include "nmea/command.hpp"

#include <iomanip>
#include <sstream>

namespace nmea {

command::command() = default;

command::command(std::string name) : m_name(name) {}

command::~command() = default;

std::string command::to_string() { return add_checksum(m_message); }

std::string command::add_checksum(std::string s) {
  std::stringstream zz;
  zz << m_name << "," << s;
  m_checksum = Parser::calc_checksum(zz.str());

  std::stringstream ss;
  std::ios_base::fmtflags prev_flags = ss.flags();

  ss << "$" << zz.str() << "*" << std::hex << std::uppercase << std::internal << std::setfill('0') << std::setw(2) << static_cast<int>(m_checksum) << "\r\n";

  // TODO(tybl): Save and restoring flags indicates they affect more than 
  // just this temporary stringstream. Is that true?
  ss.flags(prev_flags);
  return ss.str();
};

} // namespace nmea

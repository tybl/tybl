#include "nmea/Command.hpp"

#include <iomanip>
#include <sstream>

namespace nmea {

Command::Command() = default;

Command::Command(std::string name) : m_name(name) {}

Command::~Command() = default;

std::string Command::toString() { return addChecksum(m_message); }

std::string Command::addChecksum(std::string s) {
  std::stringstream zz;
  zz << m_name << "," << s;
  m_checksum = Parser::calculateChecksum(zz.str());

  std::stringstream ss;
  std::ios_base::fmtflags prev_flags = ss.flags();

  ss << "$" << zz.str() << "*" << std::hex << std::uppercase << std::internal << std::setfill('0') << std::setw(2) << (int)m_checksum << "\r\n";

  // TODO(tybl): Save and restoring flags indicates they affect more than 
  // just this temporary stringstream. Is that true?
  ss.flags(prev_flags);
  return ss.str();
};

} // namespace nmea

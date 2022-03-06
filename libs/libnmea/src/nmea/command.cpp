// License: The Unlicense (https://unlicense.org)
#include <nmea/command.hpp>

#include <nmea/sentence_parser.hpp>

#include <fmt/core.h>

#include <utility> // std::move

namespace tybl::nmea {

command::command() = default;

command::command(std::string p_name)
  : m_name(std::move(p_name)) {}

command::~command() = default;

// TODO(tybl): to_string() should be a const method
auto command::to_string() -> std::string { return add_checksum(m_message); }

auto command::add_checksum(std::string const& p_s) -> std::string {
  auto checksummed_portion = fmt::format("{},{}", m_name, p_s);
  m_checksum = sentence_parser::calc_checksum(checksummed_portion);
  return fmt::format("${}*{:02X}\r\n", checksummed_portion, m_checksum);
}

} // namespace tybl::nmea
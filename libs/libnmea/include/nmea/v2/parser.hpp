// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_PARSER_HPP
#define TYBL_NMEA_PARSER_HPP

#include "state.hpp"

#include <string_view>

struct parser {

  explicit parser(state& p_state);

  void parse(std::string_view p_input);

private:

  auto parse_gga(std::string_view p_input) -> std::string_view;

  auto parse_gsa(std::string_view p_input) -> std::string_view;

  auto parse_gsv(std::string_view p_input) -> std::string_view;

  auto parse_rmc(std::string_view p_input) -> std::string_view;

  auto parse_vtg(std::string_view p_input) -> std::string_view;

  state& m_state;
}; // struct parser
#endif // TYBL_NMEA_PARSER_HPP

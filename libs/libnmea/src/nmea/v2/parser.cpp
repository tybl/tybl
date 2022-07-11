// License: The Unlicense (https://unlicense.org)
#include <nmea/v2/parser.hpp>

#include <nmea/v2/talker_id.hpp>

#include <charconv>

parser::parser(state& p_state) : m_state(p_state) {}

void parser::parse(std::string_view p_input) {
  using namespace std::literals;
  p_input.remove_prefix(p_input.find('$') + 1); // +1 to remove `$` as well
  auto talker_id = parse_talker_id(p_input);
  if (p_input.starts_with("GGA"sv)) {
    p_input = parse_gga(p_input.substr(4));
  } else if (p_input.starts_with("GSA"sv)) {
    p_input = parse_gsa(p_input.substr(4));
  } else if (p_input.starts_with("GSV"sv)) {
    p_input = parse_gsv(p_input.substr(4));
  } else if (p_input.starts_with("RMC"sv)) {
    p_input = parse_rmc(p_input.substr(4));
  } else if (p_input.starts_with("VTG"sv)) {
    p_input = parse_vtg(p_input.substr(4));
  }
}

auto parser::parse_gga(std::string_view p_input) -> std::string_view {
  gga_sentence result{};
  m_state.apply_gga(result);
  return p_input;
}

auto parser::parse_gsa(std::string_view p_input) -> std::string_view {
  gsa_sentence result{};
  m_state.apply_gsa(result);
  return p_input;
}

auto parser::parse_gsv(std::string_view p_input) -> std::string_view {
  gsv_sentence result{};
  m_state.apply_gsv(result);
  return p_input;
}

auto parser::parse_rmc(std::string_view p_input) -> std::string_view {
  rmc_sentence result{};
  auto res = std::from_chars(p_input.begin(), p_input.end(), result.time);
  p_input.remove_prefix(static_cast<size_t>(res.ptr - p_input.begin() + 1));
  result.valid = ('A' == p_input.front());
  p_input.remove_prefix(2);
  res = std::from_chars(p_input.begin(), p_input.end(), result.latitude);
  p_input.remove_prefix(static_cast<size_t>(res.ptr - p_input.begin() + 1));
  result.latitude *= ('N' == p_input.front()) ? 1 : -1;
  p_input.remove_prefix(2);
  res = std::from_chars(p_input.begin(), p_input.end(), result.longitude);
  p_input.remove_prefix(static_cast<size_t>(res.ptr - p_input.begin() + 1));
  result.longitude *= ('E' == p_input.front()) ? 1 : -1;
  p_input.remove_prefix(2);
  res = std::from_chars(p_input.begin(), p_input.end(), result.speed);
  p_input.remove_prefix(static_cast<size_t>(res.ptr - p_input.begin() + 1));
  res = std::from_chars(p_input.begin(), p_input.end(), result.course);
  p_input.remove_prefix(static_cast<size_t>(res.ptr - p_input.begin() + 1));
  res = std::from_chars(p_input.begin(), p_input.end(), result.date);
  p_input.remove_prefix(static_cast<size_t>(res.ptr - p_input.begin() + 1));
  res = std::from_chars(p_input.begin(), p_input.end(), result.magnetic_variation);
  p_input.remove_prefix(static_cast<size_t>(res.ptr - p_input.begin() + 1));

  m_state.apply_rmc(result);
  return p_input;
}

auto parser::parse_vtg(std::string_view p_input) -> std::string_view {
  vtg_sentence result{};
  m_state.apply_vtg(result);
  return p_input;
}

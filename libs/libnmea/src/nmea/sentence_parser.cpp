// License: The Unlicense (https://unlicense.org)
#include <nmea/sentence_parser.hpp>

#include <nmea/sentence.hpp>

#include <vodka/parse_error.hpp>
#include <vodka/split.hpp>

#include <spdlog/spdlog.h>

#include <cctype>
#include <charconv>

namespace tybl::nmea {

// true if the text contains a non-alpha numeric value
static auto has_non_alpha_num(std::string_view p_txt) -> bool {
  return !std::all_of(p_txt.begin(), p_txt.end(), [](char p_char) { return static_cast<bool>(std::isalnum(p_char)); });
}

// true if alphanumeric or '-'
static auto valid_param_chars(std::string_view p_txt) -> bool {
  return std::all_of(p_txt.begin(), p_txt.end(), [](char p_char) {
    return static_cast<bool>(std::isalnum(p_char)) || '-' == p_char || '.' == p_char;
  });
}

static void squish(std::string& p_str) {
  std::erase(p_str, '\t'); // Remove tabs
  std::erase(p_str, ' ');  // Remove spaces
}

// --------- NMEA PARSER --------------

void sentence_parser::set_sentence_handler(const std::string& p_cmd_key,
                                           const std::function<void(const sentence&)>& p_handler) {
  m_event_table.insert_or_assign(p_cmd_key, p_handler);
}

// takes a complete NMEA string and gets the data bits from it,
// calls the corresponding handler in m_event_table, based on the 5 letter sentence code
void sentence_parser::read_sentence(std::string p_cmd) {

  spdlog::info("Processing NEW string...");

  if (p_cmd.empty()) {
    spdlog::warn("Blank string -- Skipped processing.");
    return;
  }

  // If there is a newline at the end (we are coming from the byte reader
  if (*(p_cmd.end() - 1) == '\n') {
    if (*(p_cmd.end() - 2) == '\r') { // if there is a \r before the newline, remove it.
      p_cmd = p_cmd.substr(0, p_cmd.size() - 2);
    } else {
      spdlog::warn("Malformed newline, missing carriage return (\\r)");
      p_cmd = p_cmd.substr(0, p_cmd.size() - 1);
    }
  }

  // Remove all whitespace characters.
  size_t begin_size = p_cmd.size();
  squish(p_cmd);
  if (p_cmd.size() != begin_size) {
    spdlog::warn("New NMEA string was full of {} whitespaces!", (begin_size - p_cmd.size()));
  }

  spdlog::info("NMEA string: (\"{}\")", p_cmd);

  sentence nmea;
  // Separates the data now that everything is formatted
  try {
    parse_text(nmea, p_cmd);
  } catch (tybl::vodka::parse_error const&) {
    throw;
  } catch (std::exception const& e) {
    throw std::runtime_error(std::string(" >> NMEA sentence_parser Internal Error: Indexing error?... ") + e.what());
  }

  if (!nmea.valid()) {
    if (const size_t LINE_WIDTH = 35; LINE_WIDTH < nmea.text.size()) {
      spdlog::error("Invalid text. (\"{}\")", nmea.text.substr(0, LINE_WIDTH));
    } else {
      spdlog::error("Invalid text. (\"{}\")", nmea.text);
    }
    return;
  }

  // Call the "any sentence" event handler, even if invalid checksum, for possible logging elsewhere.
  spdlog::info("Calling generic on_sentence().");
  on_sentence(nmea);

  // Call event m_handlers based on map entries
  std::function<void(const sentence&)> handler = m_event_table[nmea.name];
  if (handler) {
    spdlog::info("Calling specific handler for sentence named \"{}\"", nmea.name);
    handler(nmea);
  } else {
    spdlog::warn("Null event handler for type named \"{}\"", nmea.name);
  }
}

auto sentence_parser::calc_checksum(std::string_view p_text) -> uint8_t {
  return std::accumulate(p_text.begin(), p_text.end(), 0,
                         [](uint8_t p_chksum, char p_char) { return static_cast<uint8_t>(p_chksum ^ p_char); });
}

void sentence_parser::parse_text(sentence& p_nmea, std::string const& p_text) const {
  p_nmea.m_is_valid = false;
  p_nmea.text = p_text;
  std::string_view text(p_nmea.text);

  if (text.empty()) {
    return;
  }

  // Looking for index of last '$'
  size_t start_byte = text.find_last_of('$');
  if (start_byte == std::string_view::npos) {
    // No dollar sign... INVALID!
    return;
  }

  // Get rid of data up to last'$'
  text = text.substr(start_byte + 1);

  // Checksum
  if (auto checksum_str_loc = text.find_last_of('*'); std::string_view::npos != checksum_str_loc) {
    p_nmea.checksum = text.substr(checksum_str_loc + 1);
    spdlog::info("Found checksum: \"*{}\"", p_nmea.checksum);
    text = text.substr(0, checksum_str_loc);
    p_nmea.m_calculated_checksum = calc_checksum(text);
    auto result = std::from_chars(p_nmea.checksum.begin(), p_nmea.checksum.end(), p_nmea.m_parsed_checksum, 16);
    p_nmea.m_is_checksum_calculated = result.ptr != p_nmea.checksum.begin();
    spdlog::info("Parsed checksum: \"*{:X}\"", p_nmea.m_parsed_checksum);
    spdlog::info("Checksum okay? {}", p_nmea.is_checksum_ok());
  } else {
    spdlog::warn("No checksum information provided");
  }

  // Handle comma edge cases
  size_t comma = text.find(',');
  if (comma == std::string_view::npos) { // comma not found, but there is a name...
    if (!text.empty()) {                 // the received data must just be the name
      if (has_non_alpha_num(text)) {
        return;
      }
      p_nmea.name = text;
      p_nmea.m_is_valid = true;
      return;
    }
    // it is a '$' with no information
    return;
  }

  //"$," case - no name
  if (comma == 0) {
    return;
  }

  // name should not include first comma
  p_nmea.name = text.substr(0, comma);
  if (has_non_alpha_num(p_nmea.name)) {
    return;
  }

  // comma is the last character/only comma
  if (comma + 1 == text.size()) {
    p_nmea.parameters.emplace_back();
    p_nmea.m_is_valid = true;
    return;
  }

  // move to data after first comma
  text = text.substr(comma + 1, text.size() - (comma + 1));

  // parse parameters according to csv
  p_nmea.parameters = tybl::vodka::split(text, ',');

  spdlog::info("Found {} parameters.", p_nmea.parameters.size());


  for (size_t i = 0; i < p_nmea.parameters.size(); i++) {
    if (!valid_param_chars(p_nmea.parameters[i])) {
      p_nmea.m_is_valid = false;
      spdlog::error("Invalid character (non-alphanumeric) in field {}: \"{}\"", i, p_nmea.parameters[i]);
      break;
    }
  }

  p_nmea.m_is_valid = true;
}

} // namespace tybl::nmea

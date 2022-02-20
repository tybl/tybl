// License: The Unlicense (https://unlicense.org)

#include <nmea/Parser.hpp>

#include <nmea/sentence.hpp>

#include <vodka/parse_error.hpp>

#include <spdlog/spdlog.h>

#include <cctype>
#include <iostream>
#include <sstream>

namespace tybl::nmea {

// true if the text contains a non-alpha numeric value
static auto has_non_alpha_num(std::string_view p_txt) -> bool {
  return !std::all_of(p_txt.begin(), p_txt.end(), [](char p_char) { return static_cast<bool>(std::isalnum(p_char)); });
}

// true if alphanumeric or '-'
static auto valid_param_chars(std::string_view p_txt) -> bool {
  return std::all_of(p_txt.begin(), p_txt.end(), [](char p_char){ return static_cast<bool>(std::isalnum(p_char)) || '-' == p_char || '.' == p_char; });
}

static void squish(std::string& p_str) {
  std::erase(p_str, '\t'); // Remove tabs
  std::erase(p_str, ' ');  // Remove spaces
}

// --------- NMEA PARSER --------------

void Parser::set_sentence_handler(const std::string& p_cmd_key, const std::function<void(const sentence&)>& p_handler) {
  m_event_table.erase(p_cmd_key);
  m_event_table.insert({p_cmd_key, p_handler});
}

// takes a complete NMEA string and gets the data bits from it,
// calls the corresponding handler in m_event_table, based on the 5 letter sentence code
void Parser::read_sentence(std::string p_cmd) {

  sentence nmea;

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

  // Separates the data now that everything is formatted
  try {
    parse_text(nmea, p_cmd);
  } catch (tybl::vodka::parse_error const&) {
    throw;
  } catch (std::exception const& e) {
    throw std::runtime_error(std::string(" >> NMEA Parser Internal Error: Indexing error?... ") + e.what());
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

// takes the string *between* the '$' and '*' in nmea sentence,
// then calculates a rolling XOR on the bytes
auto Parser::calc_checksum(std::string const& p_s) -> uint8_t {
  uint8_t checksum = 0;
  for (const char i : p_s) {
    checksum = static_cast<uint8_t>(checksum ^ i);
  }
  return checksum;
}

void Parser::parse_text(sentence& p_nmea, std::string p_txt) {

  p_nmea.m_is_valid = false; // assume it's invalid first
  if (p_txt.empty()) {
    return;
  }

  p_nmea.text = p_txt;       // save the received text of the sentence

  // Looking for index of last '$'
  size_t dollar = p_txt.find_last_of('$');
  if (dollar == std::string::npos) {
    // No dollar sign... INVALID!
    return;
  }
  auto start_byte = dollar;

  // Get rid of data up to last'$'
  p_txt = p_txt.substr(start_byte + 1);

  // Look for checksum
  size_t checkstri = p_txt.find_last_of('*');
  bool has_checksum = checkstri != std::string::npos;
  if (has_checksum) {
    // A checksum was passed in the message, so calculate what we expect to see
    p_nmea.m_calculated_checksum = calc_checksum(p_txt.substr(0, checkstri));
  } else {
    // No checksum is only a warning because some devices allow sending data with no checksum.
    spdlog::warn("No checksum information provided");
  }

  // Handle comma edge cases
  size_t comma = p_txt.find(',');
  if (comma == std::string::npos) { // comma not found, but there is a name...
    if (!p_txt.empty()) {           // the received data must just be the name
      if (has_non_alpha_num(p_txt)) {
        p_nmea.m_is_valid = false;
        return;
      }
      p_nmea.name = p_txt;
      p_nmea.m_is_valid = true;
      return;
    }
    // it is a '$' with no information
    p_nmea.m_is_valid = false;
    return;
  }

  //"$," case - no name
  if (comma == 0) {
    p_nmea.m_is_valid = false;
    return;
  }

  // name should not include first comma
  p_nmea.name = p_txt.substr(0, comma);
  if (has_non_alpha_num(p_nmea.name)) {
    p_nmea.m_is_valid = false;
    return;
  }

  // comma is the last character/only comma
  if (comma + 1 == p_txt.size()) {
    p_nmea.parameters.emplace_back("");
    p_nmea.m_is_valid = true;
    return;
  }

  // move to data after first comma
  p_txt = p_txt.substr(comma + 1, p_txt.size() - (comma + 1));

  // parse parameters according to csv
  std::istringstream f(p_txt);
  std::string s;
  while (std::getline(f, s, ',')) {
    p_nmea.parameters.push_back(s);
  }

  // above line parsing does not add a blank parameter if there is a comma at the end...
  //  so do it here.
  if (*(p_txt.end() - 1) == ',') {

    // supposed to have checksum but there is a comma at the end... invalid
    if (has_checksum) {
      p_nmea.m_is_valid = false;
      return;
    }

    // cout << "NMEA parser Warning: extra comma at end of sentence, but no information...?" << endl;    // it's
    // actually standard, if checksum is disabled
    p_nmea.parameters.emplace_back("");

    spdlog::info("Found {} parameters.", p_nmea.parameters.size());

  } else {
    spdlog::info("Found {} parameters.", p_nmea.parameters.size());

    // possible checksum at end...
    size_t endi = p_nmea.parameters.size() - 1;
    size_t checki = p_nmea.parameters[endi].find_last_of('*');
    if (checki != std::string::npos) {
      std::string last = p_nmea.parameters[endi];
      p_nmea.parameters[endi] = last.substr(0, checki);
      if (checki == last.size() - 1) {
        spdlog::error("Checksum '*' character at end, but no data");
      } else {
        p_nmea.checksum = last.substr(checki + 1, last.size() - checki); // extract checksum without '*'

        spdlog::info("Found checksum: \"*{}\"", p_nmea.checksum);

        try {
          p_nmea.m_parsed_checksum = static_cast<uint8_t>(std::stoul(p_nmea.checksum, nullptr, 16));
          p_nmea.m_is_checksum_calculated = true;
        } catch (std::invalid_argument const&) {
          spdlog::error("Parsed checksum string was not readable as hex: \"{}\"", p_nmea.checksum);
        }

        spdlog::info("Checksum okay? {}", p_nmea.is_checksum_ok());
      }
    }
  }

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
// License: The Unlicense (https://unlicense.org)
//#include "nmea/NumberConversionError.hpp"
#include "nmea/parse_error.hpp"
#include "nmea/Parser.hpp"
#include "nmea/sentence.hpp"

#include <cctype>
#include <iostream>
#include <sstream>

#define NMEA_PARSER_MAX_BUFFER_SIZE 2000

namespace nmea {

// true if the text contains a non-alpha numeric value
static bool has_non_alpha_num(std::string txt) {
  for (const char i : txt) {
    if ( !std::isalnum(i) ) {
      return true;
    }
  }
  return false;
}

// true if alphanumeric or '-'
static bool valid_param_chars(std::string txt) {
  for (const char i : txt) {
    if (!std::isalnum(i)) {
      if (i != '-' && i != '.') {
        return false;
      }
    }
  }
  return true;
}

// remove all whitespace
static void squish(std::string& str) {
  char chars[] = {'\t',' '};
  for (const char i : chars) {
    // needs include <algorithm>
    str.erase(std::remove(str.begin(), str.end(), i), str.end());
  }
}

#if 0
// remove side whitespace
static void trim(std::string& str) {
  std::stringstream trimmer;
  trimmer << str;
  str.clear();
  trimmer >> str;
}
#endif

// --------- NMEA PARSER --------------

Parser::Parser()
  : m_max_buffer_size(NMEA_PARSER_MAX_BUFFER_SIZE)
  , m_filling_buffer(false)
  , log(false)
{ }

Parser::~Parser() = default;

void Parser::set_sentence_handler(std::string cmdKey, std::function<void(const sentence&)> handler) {
  m_event_table.erase(cmdKey);
  m_event_table.insert({ cmdKey, handler });
}

std::string Parser::get_list_of_sentence_handlers() {
  if (m_event_table.empty()) {
    return ""; // TODO(tybl): empty c-string vs std::string constructor
  }

  std::ostringstream ss;
  for (auto const& table : m_event_table) {
    ss << table.first;

    if (!table.second) {
      ss << "(not callable)";
    }
    ss << ",";
  }
  std::string s = ss.str();
  if (!s.empty()) {
    s.resize(s.size()-1); // chop off comma
  }
  return s;
}

void Parser::read_byte(char b) {
  std::cerr << "Parser::read_byte(uint8_t): " << __LINE__ << " - " << static_cast<uint32_t>(b) << (std::isgraph(b) ? b : '\0') << std::endl;
  uint8_t start_byte = '$';

  if (m_filling_buffer) {
    std::cerr << "Parser::read_byte(uint8_t): " << __LINE__ << std::endl;
    if (b == '\n') {
    std::cerr << "Parser::read_byte(uint8_t): " << __LINE__ << std::endl;
      m_buffer.push_back(b);
      try {
        read_sentence(m_buffer);
        m_buffer.clear();
        m_filling_buffer = false;
      } catch (std::exception&) {
        std::cerr << "Parser::read_byte(uint8_t): " << __LINE__ << std::endl;
        // If anything happens, let it pass through, but reset the m_buffer first.
        m_buffer.clear();
        m_filling_buffer = false;
        throw;
      }
    } else {
      std::cerr << "Parser::read_byte(uint8_t): " << __LINE__ << std::endl;
      if (m_buffer.size() < m_max_buffer_size) {
        std::cerr << "Parser::read_byte(uint8_t): " << __LINE__ << std::endl;
        m_buffer.push_back(b);
      } else {
        std::cerr << "Parser::read_byte(uint8_t): " << __LINE__ << std::endl;
        m_buffer.clear();      // clear the host m_buffer so it won't overflow.
        m_filling_buffer = false;
      }
    }
  } else {
    std::cerr << "Parser::read_byte(uint8_t): " << __LINE__ << std::endl;
    if (b == start_byte) {      // only start filling when we see the start byte.
      std::cerr << "Parser::read_byte(uint8_t): " << __LINE__ << std::endl;
      m_filling_buffer = true;
      m_buffer.push_back(b);
    }
  }
}

void Parser::read_buffer(char* b, uint32_t size) {
  for (uint32_t i = 0; i < size; ++i) {
    read_byte(b[i]);
  }
}

void Parser::read_line(std::string cmd) {
  cmd += "\r\n"; // TODO(tybl): Compare operator+=() to append()
  for (const char i : cmd) {
    read_byte(i);
  }
}

// Loggers
void Parser::on_info(sentence& /*nmea*/, std::string txt) {
  if (log) {
    std::cout << "[Info]    " << txt << std::endl;
  }
}

void Parser::on_warn(sentence& /*nmea*/, std::string txt) {
  if (log) {
    std::cout << "[Warning] " << txt << std::endl;
  }
}

void Parser::on_err(sentence& /*nmea*/, std::string txt) {
  throw parse_error("[ERROR] " + txt);
}

// takes a complete NMEA string and gets the data bits from it,
// calls the corresponding handler in m_event_table, based on the 5 letter sentence code
void Parser::read_sentence(std::string cmd) {
  std::cerr << "Parser::read_sentence(std::string): " << __LINE__ << std::endl;

  sentence nmea;

  on_info(nmea, "Processing NEW string...");

  if (cmd.empty()) {
    on_warn(nmea, "Blank string -- Skipped processing.");
    return;
  }

  // If there is a newline at the end (we are coming from the byte reader
  if ( *(cmd.end()-1) == '\n') {
    if (*(cmd.end() - 2) == '\r') {  // if there is a \r before the newline, remove it.
      cmd = cmd.substr(0, cmd.size() - 2);
    } else {
      on_warn(nmea, "Malformed newline, missing carriage return (\\r) ");
      cmd = cmd.substr(0, cmd.size()-1);
    }
  }

  std::ios_base::fmtflags oldflags = std::cout.flags();

  // Remove all whitespace characters.
  size_t beginsize = cmd.size();
  squish(cmd);
  if (cmd.size() != beginsize) {
    std::stringstream ss;
    ss << "New NMEA string was full of " << (beginsize - cmd.size()) << " whitespaces!";
    on_warn(nmea, ss.str());
  }

  on_info(nmea, std::string("NMEA string: (\"") + cmd + "\")");

  // Separates the data now that everything is formatted
  try {
    parse_text(nmea, cmd);
  } catch (parse_error&) {
    throw;
  } catch (std::exception& e) {
    std::string s = " >> NMEA Parser Internal Error: Indexing error?... ";
    throw std::runtime_error(s + e.what());
  }
  std::cout.flags(oldflags);  //reset

  // Handle/Throw parse errors
  if (!nmea.valid()) {
    size_t linewidth = 35;
    std::stringstream ss;
    if (nmea.text.size() > linewidth) {
      ss << "Invalid text. (\"" << nmea.text.substr(0, linewidth) << "...\")";
    } else {
      ss << "Invalid text. (\"" << nmea.text << "\")";
    }

    on_err(nmea, ss.str());
    return;
  }

  // Call the "any sentence" event handler, even if invalid checksum, for possible logging elsewhere.
  on_info(nmea, "Calling generic onSentence().");
  onSentence(nmea);

  // Call event m_handlers based on map entries
  std::function<void(const sentence&)> handler = m_event_table[nmea.name];
  if (handler) {
    on_info(nmea, std::string("Calling specific handler for sentence named \"") + nmea.name + "\"");
    handler(nmea);
  } else {
    on_warn(nmea, std::string("Null event handler for type (name: \"") + nmea.name + "\")");
  }
  std::cout.flags(oldflags);  //reset
}

// takes the string *between* the '$' and '*' in nmea sentence,
// then calculates a rolling XOR on the bytes
uint8_t Parser::calc_checksum(std::string s) {
  uint8_t checksum = 0;
  for (const char i : s) {
    checksum = static_cast<uint8_t>(checksum ^ i);
  }

  // will display the calculated checksum in hex
  //if(log)
  //{
  //  ios_base::fmtflags oldflags = cout.flags();
  //  cout << "NMEA parser Info: calculated CHECKSUM for \""  << s << "\": 0x" << std::hex << (int)checksum << endl;
  //  cout.flags(oldflags);  //reset
  //}
  return checksum;
}

void Parser::parse_text(sentence& nmea, std::string txt) {

  if (txt.empty()) {
    nmea.m_is_valid = false;
    return;
  }

  nmea.m_is_valid = false;  // assume it's invalid first
  nmea.text = txt;    // save the received text of the sentence

  // Looking for index of last '$'
  size_t startbyte = 0;
  size_t dollar = txt.find_last_of('$');
  if (dollar == std::string::npos) {
    // No dollar sign... INVALID!
    return;
  } else {
    startbyte = dollar;
  }

  // Get rid of data up to last'$'
  txt = txt.substr(startbyte + 1);

  // Look for checksum
  size_t checkstri = txt.find_last_of('*');
  bool haschecksum = checkstri != std::string::npos;
  if (haschecksum) {
    // A checksum was passed in the message, so calculate what we expect to see
    nmea.m_calculated_checksum = calc_checksum(txt.substr(0, checkstri));
  } else {
    // No checksum is only a warning because some devices allow sending data with no checksum.
    on_warn(nmea, "No checksum information provided. Could not find '*'.");
  }

  // Handle comma edge cases
  size_t comma = txt.find(',');
  if (comma == std::string::npos) {    //comma not found, but there is a name...
    if (!txt.empty()) {  // the received data must just be the name
      if (has_non_alpha_num(txt)) {
        nmea.m_is_valid = false;
        return;
      }
      nmea.name = txt;
      nmea.m_is_valid = true;
      return;
    } else {  //it is a '$' with no information
      nmea.m_is_valid = false;
      return;
    }
  }

  //"$," case - no name
  if (comma == 0) {
    nmea.m_is_valid = false;
    return;
  }

  //name should not include first comma
  nmea.name = txt.substr(0, comma);
  if ( has_non_alpha_num(nmea.name) ) {
    nmea.m_is_valid = false;
    return;
  }

  //comma is the last character/only comma
  if (comma + 1 == txt.size()) {
    nmea.parameters.push_back("");
    nmea.m_is_valid = true;
    return;
  }

  //move to data after first comma
  txt = txt.substr(comma + 1, txt.size() - (comma + 1));

  //parse parameters according to csv
  std::istringstream f(txt);
  std::string s;
  while (std::getline(f, s, ',')) {
    //cout << s << endl;
    nmea.parameters.push_back(s);
  }

  //above line parsing does not add a blank parameter if there is a comma at the end...
  // so do it here.
  if (*(txt.end() - 1) == ',') {

    // supposed to have checksum but there is a comma at the end... invalid
    if (haschecksum) {
      nmea.m_is_valid = false;
      return;
    }

    //cout << "NMEA parser Warning: extra comma at end of sentence, but no information...?" << endl;    // it's actually standard, if checksum is disabled
    nmea.parameters.push_back("");

    std::stringstream sz;
    sz << "Found " << nmea.parameters.size() << " parameters.";
    on_info(nmea, sz.str());

  } else {
    std::stringstream sz;
    sz << "Found " << nmea.parameters.size() << " parameters.";
    on_info(nmea, sz.str());

    //possible checksum at end...
    size_t endi = nmea.parameters.size() - 1;
    size_t checki = nmea.parameters[endi].find_last_of('*');
    if (checki != std::string::npos) {
      std::string last = nmea.parameters[endi];
      nmea.parameters[endi] = last.substr(0, checki);
      if (checki == last.size() - 1) {
        on_err(nmea, "Checksum '*' character at end, but no data.");
      } else {
        nmea.checksum = last.substr(checki + 1, last.size() - checki);    //extract checksum without '*'

        on_info(nmea, std::string("Found checksum. (\"*") + nmea.checksum + "\")");

        try {
          nmea.m_parsed_checksum = static_cast<uint8_t>(std::stoul(nmea.checksum, nullptr, 16));
          nmea.m_is_checksum_calculated = true;
        } catch (std::invalid_argument&) {
          on_err(nmea, std::string("parseInt() error. Parsed checksum string was not readable as hex. (\"") +  nmea.checksum + "\")");
        }

        on_info(nmea, std::string("Checksum ok? ") + (nmea.is_checksum_ok() ? "YES" : "NO") + "!");

      }
    }
  }


  for (size_t i = 0; i < nmea.parameters.size(); i++) {
    if (!valid_param_chars(nmea.parameters[i])) {
      nmea.m_is_valid = false;
      std::stringstream ss;
      ss << "Invalid character (non-alpha-num) in parameter " << i << " (from 0): \"" << nmea.parameters[i] << "\"";
      on_err(nmea, ss.str() );
      break;
    }
  }


  nmea.m_is_valid = true;

  return;

}

} // namespace nmea

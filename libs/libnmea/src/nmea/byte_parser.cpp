// License: The Unlicense (https://unlicense.org)

#include <nmea/byte_parser.hpp>

namespace tybl::nmea {

void byte_parser::read_byte(char p_b) {
  if (m_filling_buffer) {
    m_buffer.push_back(p_b);
    if ('\n' == p_b) {
      try {
        read_sentence(m_buffer);
        m_filling_buffer = false;
        m_buffer.clear();
      } catch (std::exception&) {
        // If anything happens, let it pass through, but reset the buffer first
        m_buffer.clear();
        m_filling_buffer = false;
        throw;
      }
    }
    if (m_buffer.size() > MAX_BUFFER_SIZE) {
      m_buffer.clear();
      m_filling_buffer = false;
    }
  } else if ('$' == p_b) {
    // only start filling the buffer when we see the start byte.
    m_filling_buffer = true;
    m_buffer.push_back(p_b);
  }
}

void byte_parser::read_buffer(std::string_view p_buffer) {
  for (auto byte : p_buffer) {
    read_byte(byte);
  }
}

void byte_parser::read_line(std::string p_line) {
  p_line.append("\r\n", 2);
  read_buffer(p_line);
}

} // namespace tybl::nmea

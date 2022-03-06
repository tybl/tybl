// License: The Unlicense (https://unlicense.org)
#include <nmea/command.hpp>

#include <doctest/doctest.h>
#include <nmea/sentence_parser.hpp>

TEST_CASE("tybl::nmea::command dog food") {
  tybl::nmea::command cmd("NAME");
  bool was_run = false;
  tybl::nmea::sentence_parser parser;
  parser.set_sentence_handler("NAME", [&was_run](tybl::nmea::sentence const&){ was_run = true; });
  parser.read_sentence(cmd.to_string());
  CHECK(was_run);
}

TEST_CASE("tybl::nmea::command don't modify cmd") {
  tybl::nmea::command cmd("NAME");
  CHECK(std::string("$NAME,*2B\r\n") == cmd.to_string());
  // confirm to_string doesn't modify cmd
  CHECK(std::string("$NAME,*2B\r\n") == cmd.to_string());
  // TODO(tybl): Should to_string result in a comma being added if m_message isn't set?
}

TEST_CASE("tybl::nmea::command::to_string() zero padded") {
  tybl::nmea::command cmd("NA+ME");
  CHECK(std::string("$NA+ME,*00\r\n") == cmd.to_string());
}
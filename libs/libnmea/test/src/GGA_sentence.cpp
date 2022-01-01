// License: The Unlicense (https://unlicense.org)

#include "doctest/doctest.h"

#include <iostream>
#include <string>

namespace nmea {

struct Sentence {

  virtual ~Sentence() = default;

  virtual void parse(std::string const&) = 0;

}; // class Sentence

class GGASentence
  : public Sentence
{
public:

  virtual ~GGASentence() = default;

  void parse(std::string const& sentence) override {
    auto comma1 = sentence.find(',');
    auto comma2 = sentence.find(',',comma1);
    auto comma3 = sentence.find(',',comma2);
    std::cout << comma1 << ',' << comma2 << ',' << comma3 << std::endl;
  }

}; // class GGASentence

} // namespace nmea

TEST_CASE("NMEA GGA Sentence 1") {
  nmea::GGASentence obj;

}

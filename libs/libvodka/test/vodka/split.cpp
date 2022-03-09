#include <vodka/split.hpp>

#include <doctest/doctest.h>

TEST_CASE("tybl::vodka::split")
{
  {
    const std::string_view str = "A,B,C";
    auto tokens = tybl::vodka::split(str, ',');
    CHECK(tokens.size() == 3);
    CHECK(tokens[0] == "A");
    CHECK(tokens[1] == "B");
    CHECK(tokens[2] == "C");
  }
  {
    const std::string_view str = ",B,C";
    auto tokens = tybl::vodka::split(str, ',');
    CHECK(tokens.size() == 3);
    CHECK(tokens[0] == "");
    CHECK(tokens[1] == "B");
    CHECK(tokens[2] == "C");
  }
  {
    const std::string_view str = "A,B,";
    auto tokens = tybl::vodka::split(str, ',');
    CHECK(tokens.size() == 3);
    CHECK(tokens[0] == "A");
    CHECK(tokens[1] == "B");
    CHECK(tokens[2] == "");
  }
  {
    const std::string_view str = "";
    auto tokens = tybl::vodka::split(str, ',');
    CHECK(tokens.size() == 1);
    CHECK(tokens[0] == "");
  }
  {
    const std::string_view str =  "A";
    auto tokens = tybl::vodka::split(str, ',');
    CHECK(tokens.size() == 1);
    CHECK(tokens[0] == "A");
  }
  {
    const std::string_view str =  ",";
    auto tokens = tybl::vodka::split(str, ',');
    CHECK(tokens.size() == 2);
    CHECK(tokens[0] == "");
    CHECK(tokens[1] == "");
  }
  {
    const std::string_view str =  ",,";
    auto tokens = tybl::vodka::split(str, ',');
    CHECK(tokens.size() == 3);
    CHECK(tokens[0] == "");
    CHECK(tokens[1] == "");
    CHECK(tokens[2] == "");
  }
  {
    const std::string_view str = "A,";
    auto tokens = tybl::vodka::split(str, ',');
    CHECK(tokens.size() == 2);
    CHECK(tokens[0] == "A");
    CHECK(tokens[1] == "");
  }
  {
    const std::string_view str = ",B";
    auto tokens = tybl::vodka::split(str, ',');
    CHECK(tokens.size() == 2);
    CHECK(tokens[0] == "");
    CHECK(tokens[1] == "B");
  }
}
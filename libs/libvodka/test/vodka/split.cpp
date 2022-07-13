#include <vodka/split.hpp>

#include <doctest/doctest.h>

#include <string>

TEST_CASE("tybl::vodka::split_on<string_view>")
{
  {
    const std::string_view str = "A,B,C";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 3);
    CHECK(tokens[0] == "A");
    CHECK(tokens[1] == "B");
    CHECK(tokens[2] == "C");
  }
  {
    const std::string_view str = ",B,C";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 3);
    CHECK(tokens[0] == "");
    CHECK(tokens[1] == "B");
    CHECK(tokens[2] == "C");
  }
  {
    const std::string_view str = "A,B,";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 3);
    CHECK(tokens[0] == "A");
    CHECK(tokens[1] == "B");
    CHECK(tokens[2] == "");
  }
  {
    const std::string_view str = "";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 1);
    CHECK(tokens[0] == "");
  }
  {
    const std::string_view str =  "A";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 1);
    CHECK(tokens[0] == "A");
  }
  {
    const std::string_view str =  ",";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 2);
    CHECK(tokens[0] == "");
    CHECK(tokens[1] == "");
  }
  {
    const std::string_view str =  ",,";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 3);
    CHECK(tokens[0] == "");
    CHECK(tokens[1] == "");
    CHECK(tokens[2] == "");
  }
  {
    const std::string_view str = "A,";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 2);
    CHECK(tokens[0] == "A");
    CHECK(tokens[1] == "");
  }
  {
    const std::string_view str = ",B";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 2);
    CHECK(tokens[0] == "");
    CHECK(tokens[1] == "B");
  }
}

TEST_CASE("tybl::vodka::split_on<string>")
{
  {
    const std::string str = "A,B,C";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 3);
    CHECK(tokens[0] == "A");
    CHECK(tokens[1] == "B");
    CHECK(tokens[2] == "C");
  }
  {
    const std::string str = ",B,C";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 3);
    CHECK(tokens[0] == "");
    CHECK(tokens[1] == "B");
    CHECK(tokens[2] == "C");
  }
  {
    const std::string str = "A,B,";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 3);
    CHECK(tokens[0] == "A");
    CHECK(tokens[1] == "B");
    CHECK(tokens[2] == "");
  }
  {
    const std::string str = "";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 1);
    CHECK(tokens[0] == "");
  }
  {
    const std::string str =  "A";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 1);
    CHECK(tokens[0] == "A");
  }
  {
    const std::string str =  ",";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 2);
    CHECK(tokens[0] == "");
    CHECK(tokens[1] == "");
  }
  {
    const std::string str =  ",,";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 3);
    CHECK(tokens[0] == "");
    CHECK(tokens[1] == "");
    CHECK(tokens[2] == "");
  }
  {
    const std::string str = "A,";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 2);
    CHECK(tokens[0] == "A");
    CHECK(tokens[1] == "");
  }
  {
    const std::string str = ",B";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 2);
    CHECK(tokens[0] == "");
    CHECK(tokens[1] == "B");
  }
}

TEST_CASE("tybl::vodka::split_on<char const*>")
{
  {
    auto str = "A,B,C";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 3);
    CHECK(tokens[0] == "A");
    CHECK(tokens[1] == "B");
    CHECK(tokens[2] == "C");
  }
  {
    auto str = ",B,C";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 3);
    CHECK(tokens[0] == "");
    CHECK(tokens[1] == "B");
    CHECK(tokens[2] == "C");
  }
  {
    auto str = "A,B,";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 3);
    CHECK(tokens[0] == "A");
    CHECK(tokens[1] == "B");
    CHECK(tokens[2] == "");
  }
  {
    auto str = "";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 1);
    CHECK(tokens[0] == "");
  }
  {
    auto str =  "A";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 1);
    CHECK(tokens[0] == "A");
  }
  {
    auto str =  ",";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 2);
    CHECK(tokens[0] == "");
    CHECK(tokens[1] == "");
  }
  {
    auto str =  ",,";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 3);
    CHECK(tokens[0] == "");
    CHECK(tokens[1] == "");
    CHECK(tokens[2] == "");
  }
  {
    auto str = "A,";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 2);
    CHECK(tokens[0] == "A");
    CHECK(tokens[1] == "");
  }
  {
    auto str = ",B";
    auto tokens = tybl::vodka::split_on(str, ',');
    CHECK(tokens.size() == 2);
    CHECK(tokens[0] == "");
    CHECK(tokens[1] == "B");
  }
}

// License: The Unlicense (https://unlicense.org)
#include "cli/Command.hpp"

#include "doctest/doctest.h"
#include "vodka/string_view/basic_string_view.hpp"

#include <cstdlib>
#include <ctime>

TEST_CASE("tasklib/cli/Command") {
  // Setup
  std::srand(std::time(nullptr));
  int result = rand();
  //  Command
  ogre::Command cmd("git");
  cmd.add_action([result](ogre::Parameters const& /*args*/) -> int { return result; });
  //  Input
  std::vector<tybl::vodka::string_view> input { "git" };

  // Execute
  CHECK(result == cmd.run(input));
}

TEST_CASE("tasklib/cli/Command subcommand") {
  // Setup
  int result = rand();
  //  Command
  ogre::Command cmd("git");
  auto& add = cmd.add_subcommand("add");
  add.add_action([result](ogre::Parameters const& args) -> int {
    CHECK(args.Arguments.front() == "main.cpp");
    return result;
  });
  //  Input
  std::vector<tybl::vodka::string_view> input { "git", "add", "main.cpp" };

  // Execute
  CHECK(result == cmd.run(input));
}

TEST_CASE("tasklib/cli/Command option") {
  // Setup
  int result = rand();
  //  Command
  ogre::Command cmd("git");
  auto& rm = cmd.add_subcommand("rm");
  rm.add_option("-f", "--force")
    .add_help("Override the up-to-date check.");
  rm.add_option("-r")
    .add_help("Allow recursive removal when leading directory name is given.");
  rm.add_action([result](ogre::Parameters const& args) -> int {
    REQUIRE(args.Options.contains("-f"));
    CHECK(args.Options.at("-f") == "true");
    REQUIRE(args.Options.contains("--force"));
    CHECK(args.Options.at("--force") == "true");
    CHECK(!args.Options.contains("-r"));
    CHECK(args.Arguments.front() == "main.cpp");
    return result;
  });
  //  Input
  std::vector<tybl::vodka::string_view> input { "git", "rm", "-f", "main.cpp" };

  // Execute
  CHECK(result == cmd.run(input));
}

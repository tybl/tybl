// License: The Unlicense (https://unlicense.org)
#pragma once

#include "Command.hpp"

#include "vodka/string_view/basic_string_view.hpp"

#include <vector>

namespace ogre {

class Application {
  Command mCommand;
  tybl::vodka::string_view mVersion;
public:

  Application(tybl::vodka::string_view name, tybl::vodka::string_view version)
    : mCommand(name)
    , mVersion(version)
  {
    // The ctor receives the app name and version. It doesn't receive the
    // command-line arguments. As such, it is not aware of any overridden
    // configuration values.
    mCommand.add_option("-v", "--version")
            .add_help("Displays the version and exits");
    mCommand.add_subcommand("add")
            .add_help("")
            .add_action([](Parameters const&) -> int { return 0; });
  }

  auto run(int argc, char const* argv[]) -> int {
    std::vector<tybl::vodka::string_view> args(argv, argv + argc);
    return mCommand.run(args);
  }

}; // class Application

} // namespace ogre

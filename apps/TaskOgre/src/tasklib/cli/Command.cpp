// License: The Unlicense (https://unlicense.org)
#include "Command.hpp"

#include <cassert>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <span>
#include <stdexcept> // std::runtime_error
#include <variant>
#include <vector>

namespace ogre {

auto Option::add_help(tybl::vodka::string_view help) -> Option& {
  mHelp = help;
  return *this;
}

void Option::parse(std::span<tybl::vodka::string_view> args, Parameters& params) {
  if (args.empty()) {
    throw std::runtime_error("Error: Unknown option");
  }
  if (!is_invoked_option(args.front())) {
    throw std::runtime_error("Error: Invoked command with different name");
  }
  for (auto name : mNames) {
    params.Options[name] = "true";
  }
}

[[nodiscard]] inline auto Option::is_invoked_option(tybl::vodka::string_view name) const -> bool {
  return mNames.end() != std::find(mNames.begin(), mNames.end(), name);
}

// auto Command::add_help(tybl::vodka::string_view help) -> Command& {
// mHelp = help;
// return *this;
//}

auto Command::add_action(callback action) -> Command& {
  mAction = std::move(action);
  return *this;
}

auto Command::get_subcommand(tybl::vodka::string_view sv) -> Command& {
  return *std::get<command_iter>(mStrToParamMap.at(sv));
}

auto Command::get_option(tybl::vodka::string_view sv) -> Option& {
  return *std::get<option_iter>(mStrToParamMap.at(sv));
}

// parse() constructs an Action object containing the callable object
// and the parameters to provide to it. All parameters are provided as
// strings on the command line, so they are provided as strings to the
// callable object.
auto Command::run(std::span<tybl::vodka::string_view> args) -> int {
  Parameters params;
  auto action = parse(args, params);
  return action(params);
}

[[nodiscard]] inline auto Command::is_invoked_command(tybl::vodka::string_view name) const -> bool {
  return names().end() != std::find(names().begin(), names().end(), name);
}

auto Command::parse(std::span<tybl::vodka::string_view> args, Parameters& params) -> Command::callback& {
  if (args.empty()) {
    throw std::runtime_error("Error: Unknown command");
  }
  if (!is_invoked_command(args.front())) {
    throw std::runtime_error("Error: Command invoked with incorrect name");
  }
  args = args.subspan(1);
  while (!args.empty()) {
    auto sub = mStrToParamMap.find(args.front());
    if (mStrToParamMap.end() != sub) {
      // The argument is an option or subcommand
      if (std::holds_alternative<command_iter>(sub->second)) {
        return std::get<command_iter>(sub->second)->parse(args, params);
      }
      // assert(std::holds_alternative<option_iter>(sub->second));
      std::get<option_iter>(sub->second)->parse(args, params);
    } else {
      params.Arguments.push_back(args.front());
    }
    args = args.subspan(1);
  }
  return mAction;
}

} // namespace ogre

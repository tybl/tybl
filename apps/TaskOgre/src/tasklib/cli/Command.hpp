// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_TASKOGRE_TASKLIB_CLI_COMMAND_HPP
#define TYBL_TASKOGRE_TASKLIB_CLI_COMMAND_HPP

#include "vodka/string_view/basic_string_view.hpp"

#include <functional> // std::function
#include <map>        // std::map
#include <span>       // std::span
#include <vector>     // std::vector

#include <iostream>
#include <list>
//#include <stdexcept>
#include <variant>

namespace ogre {

struct Parameters {
  std::map<tybl::vodka::string_view, tybl::vodka::string_view> Options;
  std::vector<tybl::vodka::string_view> Arguments;
}; // struct Parameters

class Option {

  // - mNames: All the names that can be used to supply a parameter
  std::vector<tybl::vodka::string_view> mNames;

  // - mHelp: A description of the parameter
  tybl::vodka::string_view mHelp;

public:

  template <typename... Args>
  Option(Args... names)
    : mNames{names...} { }

  virtual ~Option() = default;

  virtual auto add_help(tybl::vodka::string_view help) -> Option&;

  void parse(std::span<tybl::vodka::string_view> args, Parameters& params);

  auto names() const -> std::vector<tybl::vodka::string_view> const&;

  [[nodiscard]] inline auto
  is_invoked_option(tybl::vodka::string_view name) const -> bool;

}; // class Option

// A command can have multiple names
// A command can have help text
class Command
  : public Option
{
  using command_iter = std::list<Command>::iterator;
  using option_iter = std::list<Option>::iterator;
  using param_iter = std::variant<command_iter, option_iter>;
  using callback = std::function<int(Parameters const&)>;

  // Members used to specify a command:

  // - mNames: All the names that can be used to invoke the command
  //std::vector<tybl::vodka::string_view> mNames;

  // - mHelp: A description of how to use the command
  //tybl::vodka::string_view mHelp;

  callback mAction;

  std::list<Command> mSubcommands;
  std::list<Option> mOptions;
  std::map<tybl::vodka::string_view, param_iter> mStrToParamMap;
public:

  template <typename... Args>
  Command(Args... names)
    : Option{names...} {}

  virtual ~Command() = default;

  virtual auto add_help(tybl::vodka::string_view help) -> Command&;

  template <typename... Args>
  auto add_subcommand(Args&&... names) -> Command& {
    auto new_subcommand = mSubcommands.emplace(mSubcommands.cend(), std::forward<Args>(names)...);
    index_parameter(new_subcommand);
    return mSubcommands.back();
  }

  template <typename... Args>
  auto add_option(Args&&... names) -> Option& {
    auto new_option = mOptions.emplace(std::cend(mOptions), std::forward<Args>(names)...);
    index_parameter(new_option);
    return mOptions.back();
  }

  auto add_action(callback action) -> Command&;

  auto get_subcommand(tybl::vodka::string_view sv) -> Command&;

  auto get_option(tybl::vodka::string_view sv) -> Option&;

  // parse() constructs an Action object containing the callable object
  // and the parameters to provide to it. All parameters are provided as
  // strings on the command line, so they are provided as strings to the
  // callable object.
  int run(std::span<tybl::vodka::string_view> args);

private:

  [[nodiscard]] inline auto
  is_invoked_command(tybl::vodka::string_view name) const -> bool;

  callback& parse(std::span<tybl::vodka::string_view> args, Parameters& params);

  template <typename Iterator>
  void index_parameter(Iterator pParamIter) {
    for (auto const& name : pParamIter->names()) {
      mStrToParamMap.insert_or_assign(name, pParamIter);
    }
  }

}; // class Command

} // namespace ogre

#endif // TYBL_TASKOGRE_TASKLIB_CLI_COMMAND_HPP
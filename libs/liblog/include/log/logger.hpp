// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LOG_LOGGER_HPP
#define TYBL_LOG_LOGGER_HPP

#include <fmt/core.h>

#include <string>
#include <string_view>

namespace tybl::log {

void log(std::string const& p_output);

template <typename... Args>
void log(fmt::format_string<Args...> p_format, Args&&... p_args) {
  auto message = fmt::format(p_format, std::forward<Args>(p_args)...);
  log(message);
}

} // namespace tybl::log

#endif // TYBL_LOG_LOGGER_HPP
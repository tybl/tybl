// License: The Unlicense (https://unlicense.org)
#ifndef TYBL_LIBPIM_TASK_HPP
#define TYBL_LIBPIM_TASK_HPP

#include <chrono>
#include <optional>
#include <string>

namespace tybl::taskdb {

struct Task {
  std::chrono::time_point                 m_creation_time;
  std::optional<std::chrono::time_point>  m_completion_time;
  std::string                             m_summary_text;
}; // struct Task

} // namespace tybl::taskdb

#endif // TYBL_LIBPIM_TASK_HPP

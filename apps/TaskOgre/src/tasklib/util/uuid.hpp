// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_TASKOGRE_TASKLIB_UTIL_UUID_HPP
#define TYBL_TASKOGRE_TASKLIB_UTIL_UUID_HPP

#include <compare>
#include <string>

namespace vodka::util {

class uuid {
  std::string mValue;

public:
  uuid();

  static auto Create() -> uuid;

  [[nodiscard]] auto operator<=>(uuid const&) const = default;

  [[nodiscard]] auto to_string() const -> std::string const&;

private:
  static constexpr const auto uuid_file = "/proc/sys/kernel/random/uuid";

  static constexpr const auto nil = "00000000-0000-0000-0000-000000000000";

  explicit uuid(std::string value);

  static auto GenerateStr() -> std::string;

}; // struct Uuid

} // namespace vodka::util

#endif // TYBL_TASKOGRE_TASKLIB_UTIL_UUID_HPP
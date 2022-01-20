// License: The Unlicense (https://unlicense.org)
#include "uuid.hpp"

#include <fstream> // for std::ifstream
#include <utility> // for std::move

namespace vodka::util {

uuid::uuid()
  : mValue(nil) {}

auto uuid::Create() -> uuid { return uuid(GenerateStr()); }

auto uuid::to_string() const -> std::string const& { return mValue; }

uuid::uuid(std::string value)
  : mValue(std::move(value)) {}

auto uuid::GenerateStr() -> std::string {
  std::string result;
  std::ifstream in(uuid_file, std::ios::in | std::ios::binary);
  if (in) {
    std::getline(in, result);
  }
  return result;
}

} // namespace vodka::util

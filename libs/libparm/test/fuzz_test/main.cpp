// License: The Unlicense (https://unlicense.org)

#include "parm/Application.hpp"

#include <fuzzer/FuzzedDataProvider.h>

inline std::vector<std::string> RandomStrings(const uint8_t* data, size_t size)
{
  FuzzedDataProvider fdp(data, size);
  std::vector<std::string> result;
  while (0 < fdp.remaining_bytes()) {
    result.push_back(fdp.ConsumeRandomLengthString(fdp.remaining_bytes()));
  }
  return result;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  parm::Application app("name", "version");
  app.add_argument("--verbose");
  return 0;
}

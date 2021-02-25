// License: The Unlicense (https://unlicense.org)

#include <fuzzer/FuzzedDataProvider.h>

inline void RandomStrings(const uint8_t* data, size_t size)
{
  FuzzedDataProvider fdp(data, size);
  std::vector<std::string> result;
  while (0 < fdp.remaining_bytes()) {
    result.push_back(fdp.ConsumeRandomLengthString(fdp.remaining_bytes()));
  }
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  RandomStrings(data, size);
  return 0;
}

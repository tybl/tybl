// License: The Unlicense (https://unlicense.org)
#include "stringify_arguments.hpp"

namespace ledger::util {

std::vector<std::string> stringify_arguments(int argc, const char* argv[]) {
   std::vector<std::string> args;
   for (int i = 1; i < argc; ++i) {
      args.emplace_back(argv[i]);
   }
   return args;
} // stringify_arguments()

} // namespace ledger::util

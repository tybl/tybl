// License: The Unlicense (https://unlicense.org)
#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest/doctest.h"

static int run_unit_tests(int argc, const char* argv[]) {
  doctest::Context context; // Initialize doctest context

  // defaults
  context.setOption("abort-after", 5);
  context.setOption("sort", "name");

  context.applyCommandLine(argc, argv);

  context.setOption("no-breaks", true);

  int result = context.run();
  if (context.shouldExit()) {
    exit(result);
  }
  return result;
}

extern "C" int main(int argc, const char* argv[]) { return run_unit_tests(argc, argv); }

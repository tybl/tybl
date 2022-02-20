################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

include(FetchContent)

FetchContent_Declare(doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_SHALLOW    TRUE
  GIT_TAG        "v2.4.8")
FetchContent_MakeAvailable(doctest)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_SHALLOW    TRUE
  GIT_TAG        "8.1.1")
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_SHALLOW    TRUE
  GIT_TAG        "v1.9.2")
FetchContent_MakeAvailable(spdlog)
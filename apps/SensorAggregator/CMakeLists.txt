################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

project(SensorAggregator
  VERSION 0.0.1
  DESCRIPTION "Tools to collect environment data"
  LANGUAGES CXX)

include(FetchContent)
include(util/cmake/CompilerSettings.cmake)
include(util/cmake/Linters.cmake)

find_package(Boost REQUIRED system)
find_package(Threads)

set(JSON_BuildTests OFF)
set(JSON_Install OFF)
FetchContent_Declare(nlohmann_json
	GIT_REPOSITORY https://github.com/nlohmann/json.git
	GIT_SHALLOW    TRUE
	GIT_TAG        "v3.9.1")
FetchContent_MakeAvailable(nlohmann_json)

add_subdirectory(app)

################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(json INTERFACE)
target_include_directories(json INTERFACE include)
#[[
target_link_libraries(json PUBLIC compiler_settings)
target_sources(json
  PUBLIC
    include/json/value.hpp
)
]]

add_executable(json_t)
target_link_libraries(json_t PRIVATE compiler_settings json test_base vodka)
target_sources(json_t
  PRIVATE
    test/json/main.cpp
)

add_test(NAME test_json COMMAND json_t)

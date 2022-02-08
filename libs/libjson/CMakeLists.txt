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

add_executable(test_libjson)
target_link_libraries(test_libjson PRIVATE compiler_settings json test_base vodka)
target_sources(test_libjson
  PRIVATE
    test/json/main.cpp
)

add_test(NAME libjson_test COMMAND test_libjson)

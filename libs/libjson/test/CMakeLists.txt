################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_executable(json_t)
target_link_libraries(json_t PRIVATE compiler_settings json test_base vodka)
target_sources(json_t
  PRIVATE
    src/main.cpp
)

add_test(NAME test_json COMMAND json_t)

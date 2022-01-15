################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

#[[ 
# TODO: Create unit tests
add_executable(libcoord_t)
target_link_libraries(libcoord_t PRIVATE compiler_settings test_base)
target_sources(libcoord_t
  PRIVATE
)
add_test(NAME test_libcoord COMMAND libcoord_t)
]]

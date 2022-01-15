################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

#[[ 
# TODO: Create unit tests
add_executable(libsymbolic_t)
target_link_libraries(libsymbolic_t PRIVATE compiler_settings test_base)
target_sources(libsymbolic_t
  PRIVATE
)
add_test(NAME test_libsymbolic COMMAND libsymbolic_t)
]]

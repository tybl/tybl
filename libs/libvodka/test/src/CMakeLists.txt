################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

# Define unittests executable target
add_executable(unit_test)
target_link_libraries(unit_test
  PRIVATE
    compiler_settings
    doctest::doctest
    vodka)
target_sources(unit_test
  PRIVATE
    main.cpp
    vodka/utility/forward.cpp
)
add_test(NAME unit_test_t COMMAND unit_test)

add_executable(integral_constant)
target_link_libraries(integral_constant PRIVATE compiler_settings vodka)
target_sources(integral_constant PRIVATE vodka/type_traits/integral_constant.cpp)
add_test(NAME integral_constant_t COMMAND integral_constant)

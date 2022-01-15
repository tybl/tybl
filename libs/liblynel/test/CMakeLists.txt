################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_executable(lynel_t)
target_link_libraries(lynel_t PRIVATE compiler_settings test_base lynel vodka)
target_sources(lynel_t
  PRIVATE
    src/books/LinearAlgebra_TheoryIntuitionCode.cpp
    src/lynel/matrix.cpp
)

add_test(NAME test_lynel COMMAND lynel_t)

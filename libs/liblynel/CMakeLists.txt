################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(lynel INTERFACE)
target_include_directories(lynel INTERFACE include)
target_link_libraries(lynel INTERFACE compiler_settings)
target_sources(lynel
  INTERFACE
    include/lynel/basic_matrix.hpp
    include/lynel/matrix.hpp
    include/lynel/quaternion.hpp
)

add_executable(lynel_t)
target_link_libraries(lynel_t PRIVATE compiler_settings test_base lynel vodka)
target_sources(lynel_t
  PRIVATE
    test/books/LinearAlgebra_TheoryIntuitionCode.cpp
    test/lynel/matrix.cpp
)

add_test(NAME test_lynel COMMAND lynel_t)

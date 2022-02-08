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

add_executable(test_liblynel)
target_link_libraries(test_liblynel PRIVATE compiler_settings test_base lynel vodka)
target_sources(test_liblynel
  PRIVATE
    test/books/LinearAlgebra_TheoryIntuitionCode.cpp
    test/lynel/matrix.cpp
)

add_test(NAME liblynel_test COMMAND test_liblynel)

################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(comp_test)
if(CLANG_TIDY_EXE)
  set_target_properties(comp_test PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND_LINE}")
endif()
if(CPPCHECK_EXE)
  set_target_properties(comp_test PROPERTIES CXX_CPPCHECK "${CPPCHECK_COMMAND_LINE}")
endif()
target_link_libraries(comp_test PRIVATE compiler_settings vodka)
target_sources(comp_test
  PRIVATE
    vodka/algorithm/max.cpp
    vodka/array/array.cpp
    vodka/functional/less_equal.cpp
    vodka/span/span.cpp
    vodka/string_view/basic_string_view.cpp
    vodka/type_traits/false_type.cpp
    vodka/type_traits/true_type.cpp
    vodka/type_traits/is_void.cpp)

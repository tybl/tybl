################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # relative path target_sources()

add_library(vodka INTERFACE)
target_include_directories(vodka INTERFACE include)
target_sources(vodka
  INTERFACE
    include/vodka/array/array.hpp
    include/vodka/array/get.hpp
    include/vodka/array/to_array.hpp
    include/vodka/type_traits/integral_constant.hpp
    include/vodka/type_traits/remove_const.hpp
    include/vodka/type_traits/remove_cv.hpp
    include/vodka/type_traits/remove_volatile.hpp
    include/vodka/type_traits/remove_reference.hpp
    include/vodka/utility/forward.hpp
    include/vodka/utility/move.hpp)

add_subdirectory(test)

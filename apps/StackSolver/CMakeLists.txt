################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "10.1")

	#[[
add_executable(find_all)
target_compile_features(find_all PUBLIC cxx_std_20) # 20: std::set::emplace(), std::ranges
target_sources(find_all
  PRIVATE
    src/find_all.cpp
)
]]

add_library(stacksolvelib)
target_compile_features(stacksolvelib PUBLIC cxx_std_20) # 20: std::set::emplace()
target_compile_options(stacksolvelib PUBLIC -Wall -Wextra -Wpedantic)
target_include_directories(stacksolvelib PUBLIC src)
target_link_libraries(stacksolvelib PUBLIC log)
target_sources(stacksolvelib
  PRIVATE
    src/executor.cpp
    src/i_node.cpp
    src/Board.cpp
)

add_executable(stacksolve)
target_link_libraries(stacksolve PRIVATE stacksolvelib)
target_sources(stacksolve PRIVATE src/main.cpp)

  add_executable(stacksolver_t)
  target_link_libraries(stacksolver_t PRIVATE compiler_settings test_base stacksolvelib)
  target_sources(stacksolver_t
    PRIVATE
      test/src/Board.cpp
      test/src/stacksolve/stack_state.cpp
  )

  add_test(NAME test_stacksolver COMMAND stacksolver_t)

else()
  message("Note: Not building \"StackSolver\"; install gcc > v10.1 to enable")
endif()

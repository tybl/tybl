################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_executable(stacksolver_t)
target_link_libraries(stacksolver_t PRIVATE compiler_settings test_base stacksolvelib)
target_sources(stacksolver_t
  PRIVATE
    src/Board.cpp
        src/stacksolve/stack_state.cpp
)

add_test(NAME test_stacksolver COMMAND stacksolver_t)

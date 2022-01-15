################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_executable(cocles)
target_link_libraries(cocles PRIVATE compiler_settings)
target_sources(cocles PRIVATE src/cocles.cpp)

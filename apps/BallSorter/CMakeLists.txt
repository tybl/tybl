################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

project(BallSorter
	VERSION 1.0.0
	DESCRIPTION "Solves to ball/bubble sorting games"
	LANGUAGES CXX)

add_executable(sort src/main.cpp src/Executor.cpp src/Board.cpp)
target_compile_features(sort PRIVATE cxx_std_20) # 17: std::filesystem, 20: std::set::emplace()
target_compile_options(sort PRIVATE -Wall -Wextra -Wpedantic)

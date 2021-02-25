################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_executable(collect)
target_link_libraries(collect PRIVATE
	compiler_settings
	Boost::system
        nlohmann_json::nlohmann_json
	Threads::Threads)
target_sources(collect
	PRIVATE
	collect/main.cpp
	collect/server.cpp)

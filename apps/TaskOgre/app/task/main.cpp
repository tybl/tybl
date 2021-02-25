// License: The Unlicense (https://unlicense.org)

#include "cli/Application.hpp"

#include <iostream>

auto main(int argc, char const* argv[]) -> int {
  try {
    ogre::Application app(PROJECT_NAME, PROJECT_VERSION);
    return app.run(argc, argv);
  } catch (std::exception& err) {
    std::cerr << "Error: " << err.what() << std::endl;
  }
  return -1;
}

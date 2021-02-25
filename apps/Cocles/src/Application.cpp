// License: The Unlicense (https://unlicense.org)
#include "Application.hpp"

#include <stdexcept>

std::atomic<bool> Application::mInstanceExists = false;

Application::Application(std::vector<std::string> args, const char* envp[]) {
   static_cast<void>(args);
   static_cast<void>(envp);

   if (mInstanceExists) {
      throw std::runtime_error(
          "Error: An instance of Application already exists");
   }
   mInstanceExists = true;
}

Application::~Application() { mInstanceExists = false; }

int Application::run() { return 0; }

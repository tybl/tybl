// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COCLES_APPLICATION_HPP
#define TYBL_COCLES_APPLICATION_HPP

#include <atomic>
#include <string>
#include <vector>

struct Application {

   Application(std::vector<std::string> args, const char* envp[]);

   ~Application();

   int run();

   // Deleted functions
   Application(Application const&) = delete;
   Application(Application&&) = delete;
   Application& operator=(Application) = delete;
   Application& operator=(Application&&) = delete;

private:
   static std::atomic<bool> mInstanceExists;
}; // class Application

#endif // TYBL_COCLES_APPLICATION_HPP

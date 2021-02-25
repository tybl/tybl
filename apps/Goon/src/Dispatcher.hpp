// License: The Unlicense (https://unlicense.org)
#ifndef GOON_DISPATCHER_HPP
#define GOON_DISPATCHER_HPP

#include <SDL2/SDL.h>
#include <functional>
#include <vector>

struct Dispatcher {
   Dispatcher(void);
   bool KeepRunning(void) const;
   void ProcessEvents(void);
   void AddKeyboardListener(std::function<void(SDL_Keycode)> func);
   void AddWindowListener(std::function<void(SDL_WindowEvent)> func);
private:
   void OptOutEvents(void);
private:
   std::vector<std::function<void(SDL_Keycode)>> mKeyboardListeners;
   std::vector<std::function<void(SDL_WindowEvent)>> mWindowListeners;
   bool mKeepRunning;
};
#endif // GOON_DISPATCHER_HPP

// License: The Unlicense (https://unlicense.org)
#include "Dispatcher.hpp"

#include <cstdio>

Dispatcher::Dispatcher(void)
  : mKeyboardListeners()
  , mWindowListeners()
  , mKeepRunning(true) {
  OptOutEvents();
}

bool Dispatcher::KeepRunning(void) const { return mKeepRunning; }

void Dispatcher::ProcessEvents(void) {
  SDL_Event e;
  while (0 != SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT: mKeepRunning = false; break;
      case SDL_WINDOWEVENT:
        for (auto f : mWindowListeners) {
          f(e.window);
        }
        break;
      case SDL_KEYDOWN:
        switch (e.key.keysym.sym) {
          case SDLK_DOWN:
          case SDLK_UP:
          case SDLK_LEFT:
          case SDLK_RIGHT:
            for (auto f : mKeyboardListeners) {
              f(e.key.keysym.sym);
            }
            break;
          default:
            // Ignore all other keys
            break;
        }
        break;
      default: printf("Something happened!\n"); break;
    } // switch
  }   // while
}

void Dispatcher::AddKeyboardListener(std::function<void(SDL_Keycode)> func) { mKeyboardListeners.push_back(func); }

void Dispatcher::AddWindowListener(std::function<void(SDL_WindowEvent)> func) { mWindowListeners.push_back(func); }

void Dispatcher::OptOutEvents(void) {
  SDL_EventState(SDL_APP_TERMINATING, SDL_IGNORE);
  SDL_EventState(SDL_APP_LOWMEMORY, SDL_IGNORE);
  SDL_EventState(SDL_APP_WILLENTERBACKGROUND, SDL_IGNORE);
  SDL_EventState(SDL_APP_DIDENTERBACKGROUND, SDL_IGNORE);
  SDL_EventState(SDL_APP_WILLENTERFOREGROUND, SDL_IGNORE);
  SDL_EventState(SDL_APP_DIDENTERFOREGROUND, SDL_IGNORE);
  SDL_EventState(SDL_AUDIODEVICEADDED, SDL_IGNORE);
  SDL_EventState(SDL_AUDIODEVICEREMOVED, SDL_IGNORE);
  SDL_EventState(SDL_CLIPBOARDUPDATE, SDL_IGNORE);
  SDL_EventState(SDL_CONTROLLERAXISMOTION, SDL_IGNORE);
  SDL_EventState(SDL_CONTROLLERBUTTONDOWN, SDL_IGNORE);
  SDL_EventState(SDL_CONTROLLERBUTTONUP, SDL_IGNORE);
  SDL_EventState(SDL_CONTROLLERDEVICEADDED, SDL_IGNORE);
  SDL_EventState(SDL_CONTROLLERDEVICEREMAPPED, SDL_IGNORE);
  SDL_EventState(SDL_CONTROLLERDEVICEREMOVED, SDL_IGNORE);
  SDL_EventState(SDL_DOLLARGESTURE, SDL_IGNORE);
  SDL_EventState(SDL_DOLLARRECORD, SDL_IGNORE);
  SDL_EventState(SDL_DROPFILE, SDL_IGNORE);
  SDL_EventState(SDL_FINGERDOWN, SDL_IGNORE);
  SDL_EventState(SDL_FINGERMOTION, SDL_IGNORE);
  SDL_EventState(SDL_FINGERUP, SDL_IGNORE);
  SDL_EventState(SDL_JOYAXISMOTION, SDL_IGNORE);
  SDL_EventState(SDL_JOYBALLMOTION, SDL_IGNORE);
  SDL_EventState(SDL_JOYBUTTONDOWN, SDL_IGNORE);
  SDL_EventState(SDL_JOYBUTTONUP, SDL_IGNORE);
  SDL_EventState(SDL_JOYDEVICEADDED, SDL_IGNORE);
  SDL_EventState(SDL_JOYDEVICEREMOVED, SDL_IGNORE);
  SDL_EventState(SDL_JOYHATMOTION, SDL_IGNORE);
  SDL_EventState(SDL_KEYMAPCHANGED, SDL_IGNORE);
  SDL_EventState(SDL_KEYUP, SDL_IGNORE);
  SDL_EventState(SDL_LASTEVENT, SDL_IGNORE);
  SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
  SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);
  SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
  SDL_EventState(SDL_MOUSEWHEEL, SDL_IGNORE);
  SDL_EventState(SDL_MULTIGESTURE, SDL_IGNORE);
  SDL_EventState(SDL_RENDER_TARGETS_RESET, SDL_IGNORE);
  SDL_EventState(SDL_RENDER_DEVICE_RESET, SDL_IGNORE);
  SDL_EventState(SDL_SYSWMEVENT, SDL_IGNORE);
  SDL_EventState(SDL_TEXTEDITING, SDL_IGNORE);
  SDL_EventState(SDL_TEXTINPUT, SDL_IGNORE);
  SDL_EventState(SDL_USEREVENT, SDL_IGNORE);
}

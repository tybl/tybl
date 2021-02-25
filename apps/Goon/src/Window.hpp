// License: The Unlicense (https://unlicense.org)
#ifndef GOON_WINDOW_HPP
#define GOON_WINDOW_HPP

#include <SDL2/SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Window {
   SDL_Window *mWindow;
   int mWidth;
   int mHeight;
public:
   Window(void);
   Window(Window const&) = delete;
   ~Window(void) {
      SDL_DestroyWindow(mWindow);
   }
   Window& operator=(Window const&) = delete;
   int Width(void) const { return mWidth; }
   int Height(void) const { return mHeight; }
   void ProcessEvent(const SDL_Event &event);
   SDL_Renderer* CreateRenderer(void) {
      return SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   }
};
#endif // GOON_WINDOW_HPP

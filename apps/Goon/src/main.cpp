// License: The Unlicense (https://unlicense.org)
#include "Dispatcher.hpp"
#include "Widget.hpp"
#include "Window.hpp"

#include <SDL2/SDL.h>
#include <cstdio>

// The window renderer
static SDL_Renderer* gRenderer = nullptr;

int main(int argc, char* argv[]) {
  static_cast<void>(argc);
  static_cast<void>(argv);

  // Initialize SDL
  if (0 > SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    return -1;
  }

  // Set texture filtering to linear
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    printf("Warning: Linear texture filtering not enabled!");
  }

  Window window;
  Dispatcher dispatch;

  // Create vsynced renderer for window
  gRenderer = window.CreateRenderer();
  if (gRenderer == nullptr) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return -1;
  }
  Widget ownship(gRenderer);
  dispatch.AddKeyboardListener([&](SDL_Keycode key) { ownship.HandleKeyboardEvent(key); });
  dispatch.AddWindowListener([&](SDL_WindowEvent e) { ownship.HandleWindowEvent(e); });

  while (dispatch.KeepRunning()) {
    dispatch.ProcessEvents();

    SDL_SetRenderTarget(gRenderer, nullptr);
    // Clear screen
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
    SDL_RenderClear(gRenderer);

    ownship.Render(gRenderer);

    // Update screen
    SDL_RenderPresent(gRenderer);
  } // while (keep_running)

  // Destroy window
  SDL_DestroyRenderer(gRenderer);
  gRenderer = nullptr;

  // Quit SDL subsystems
  SDL_Quit();
  return 0;
}

// License: The Unlicense (https://unlicense.org)
#include <SDL2/SDL.h>

struct Widget {
   Widget(SDL_Renderer *renderer);

   void Render(SDL_Renderer *renderer);

   void HandleKeyboardEvent(SDL_Keycode key);
   void HandleWindowEvent(SDL_WindowEvent key);

private:
   void MoveForward(void);

private:
   double mXPos;
   double mXVelocity;
   double mYPos;
   double mYVelocity;
   double mAngle;
   double mAngleMomentum;
   int mWindowWidth;
   int mWindowHeight;
   SDL_Texture *mTexture;
};

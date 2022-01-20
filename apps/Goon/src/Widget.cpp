// License: The Unlicense (https://unlicense.org)
#include "Widget.hpp"

#include <cassert>
#include <cmath>
#include <cstdio>

static const int TEXTURE_WIDTH = 90;
static const int TEXTURE_HEIGHT = 90;

Widget::Widget(SDL_Renderer* renderer)
  : mXPos(0)
  , mXVelocity(0)
  , mYPos(0)
  , mYVelocity(0)
  , mAngle(0)
  , mAngleMomentum(0)
  , mWindowWidth(640)
  , mWindowHeight(480)
  , mTexture(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TEXTURE_WIDTH,
                               TEXTURE_HEIGHT)) {
  assert(nullptr != mTexture);
  SDL_SetRenderTarget(renderer, mTexture);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderDrawLine(renderer, TEXTURE_WIDTH / 2, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT);
  SDL_RenderDrawLine(renderer, TEXTURE_WIDTH / 2, 0, 0, TEXTURE_HEIGHT);
  SDL_RenderDrawLine(renderer, TEXTURE_WIDTH / 2, TEXTURE_HEIGHT * 2 / 3, TEXTURE_WIDTH, TEXTURE_HEIGHT);
  SDL_RenderDrawLine(renderer, TEXTURE_WIDTH / 2, TEXTURE_HEIGHT * 2 / 3, 0, TEXTURE_HEIGHT);
}

void Widget::Render(SDL_Renderer* renderer) {
  // Update position
  mAngle += mAngleMomentum;
  mXPos += mXVelocity;
  mYPos += mYVelocity;
  if (mXPos > mWindowWidth / 2)
    mXPos -= mWindowWidth;
  else if (mXPos < mWindowWidth / -2)
    mXPos += mWindowWidth;
  if (mYPos > mWindowHeight / 2)
    mYPos -= mWindowHeight;
  else if (mYPos < mWindowHeight / -2)
    mYPos += mWindowHeight;

  SDL_Rect destination = {
      static_cast<int>(mXPos), // x
      static_cast<int>(mYPos), // y
      TEXTURE_WIDTH,           // w
      TEXTURE_HEIGHT           // h
  };

  SDL_RenderCopyEx(renderer, mTexture, nullptr, &destination, mAngle, nullptr, SDL_FLIP_NONE);
  destination.x += mWindowWidth;
  SDL_RenderCopyEx(renderer, mTexture, nullptr, &destination, mAngle, nullptr, SDL_FLIP_NONE);
  destination.y += mWindowHeight;
  SDL_RenderCopyEx(renderer, mTexture, nullptr, &destination, mAngle, nullptr, SDL_FLIP_NONE);
  destination.x -= mWindowWidth;
  SDL_RenderCopyEx(renderer, mTexture, nullptr, &destination, mAngle, nullptr, SDL_FLIP_NONE);
}

void Widget::HandleKeyboardEvent(SDL_Keycode key) {
  switch (key) {
    case SDLK_SPACE:
      mXPos = 0;
      mYPos = 0;
      break;
    case SDLK_UP:
      mXVelocity += std::sin(mAngle * M_PI / 180.0) * 1;
      mYVelocity -= std::cos(mAngle * M_PI / 180.0) * 1;
      break;
    case SDLK_DOWN:
      // TODO: Figure out what ownship should do when down is pressed
      break;
    case SDLK_LEFT: mAngleMomentum -= 1; break;
    case SDLK_RIGHT: mAngleMomentum += 1; break;
    default: break;
  }
}

void Widget::HandleWindowEvent(SDL_WindowEvent e) {
  switch (e.event) {
    case SDL_WINDOWEVENT_SHOWN: printf("%d\n", __LINE__); break;
    case SDL_WINDOWEVENT_HIDDEN: printf("%d\n", __LINE__); break;
    case SDL_WINDOWEVENT_EXPOSED:
      // Received when window is resized
      printf("%d\n", __LINE__);
      break;
    case SDL_WINDOWEVENT_MOVED: printf("%d\n", __LINE__); break;
    case SDL_WINDOWEVENT_RESIZED:
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      mWindowWidth = e.data1;
      mWindowHeight = e.data2;
      break;
    case SDL_WINDOWEVENT_MINIMIZED: printf("%d\n", __LINE__); break;
    case SDL_WINDOWEVENT_MAXIMIZED: printf("%d\n", __LINE__); break;
    case SDL_WINDOWEVENT_RESTORED: printf("%d\n", __LINE__); break;
    case SDL_WINDOWEVENT_ENTER: printf("%d\n", __LINE__); break;
    case SDL_WINDOWEVENT_LEAVE: printf("%d\n", __LINE__); break;
    case SDL_WINDOWEVENT_FOCUS_GAINED: printf("%d\n", __LINE__); break;
    case SDL_WINDOWEVENT_FOCUS_LOST: printf("%d\n", __LINE__); break;
    case SDL_WINDOWEVENT_CLOSE: printf("%d\n", __LINE__); break;
    default: printf("%d\n", __LINE__); break;
  }
}

void Widget::MoveForward(void) {
  mXPos += std::sin(mAngle * M_PI / 180.0) * 10;
  mYPos += std::cos(mAngle * M_PI / 180.0) * 10;
}

// License: The Unlicense (https://unlicense.org)
#ifndef GOON_KEYBOARD_HPP
#define GOON_KEYBOARD_HPP

#include <SDL2/SDL.h>
#include <cstdio>

class Keyboard {
public:
   void ProcessEvent(const SDL_Event &event) {
      switch (event.key.keysym.sym) {
         case SDLK_0: printf("0"); break;
         case SDLK_1: printf("1"); break;
         case SDLK_2: printf("2"); break;
         case SDLK_3: printf("3"); break;
         case SDLK_4: printf("4"); break;
         case SDLK_5: printf("5"); break;
         case SDLK_6: printf("6"); break;
         case SDLK_7: printf("7"); break;
         case SDLK_8: printf("8"); break;
         case SDLK_9: printf("9"); break;
         case SDLK_a: printf("a"); break;
         case SDLK_b: printf("b"); break;
         case SDLK_c: printf("c"); break;
         case SDLK_d: printf("d"); break;
         case SDLK_e: printf("e"); break;
         case SDLK_f: printf("f"); break;
         case SDLK_g: printf("g"); break;
         case SDLK_h: printf("h"); break;
         case SDLK_i: printf("i"); break;
         case SDLK_j: printf("j"); break;
         case SDLK_k: printf("k"); break;
         case SDLK_l: printf("l"); break;
         case SDLK_m: printf("m"); break;
         case SDLK_n: printf("n"); break;
         case SDLK_o: printf("o"); break;
         case SDLK_p: printf("p"); break;
         case SDLK_q: printf("q"); break;
         case SDLK_r: printf("r"); break;
         case SDLK_s: printf("s"); break;
         case SDLK_t: printf("t"); break;
         case SDLK_u: printf("u"); break;
         case SDLK_v: printf("v"); break;
         case SDLK_w: printf("w"); break;
         case SDLK_x: printf("x"); break;
         case SDLK_y: printf("y"); break;
         case SDLK_z: printf("z"); break;
         case SDLK_BACKQUOTE: printf("`"); break;
         case SDLK_BACKSLASH: printf("\\"); break;
         case SDLK_BACKSPACE: printf("<backspace>"); break;
         case SDLK_COMMA: printf(","); break;
         case SDLK_DELETE: printf("<delete>"); break;
         case SDLK_DOWN: printf("<down arrow>"); break;
         case SDLK_END: printf("<end>"); break;
         case SDLK_EQUALS: printf("="); break;
         case SDLK_ESCAPE: printf("<escape>"); break;
         case SDLK_F1: printf("<F1>"); break;
         case SDLK_F2: printf("<F2>"); break;
         case SDLK_F3: printf("<F3>"); break;
         case SDLK_F4: printf("<F4>"); break;
         case SDLK_F5: printf("<F5>"); break;
         case SDLK_F6: printf("<F6>"); break;
         case SDLK_F7: printf("<F7>"); break;
         case SDLK_F8: printf("<F8>"); break;
         case SDLK_F9: printf("<F9>"); break;
         case SDLK_F10: printf("<F10>"); break;
         case SDLK_F11: printf("<F11>"); break;
         case SDLK_F12: printf("<F12>"); break;
         case SDLK_F13: printf("<F13>"); break;
         case SDLK_F14: printf("<F14>"); break;
         case SDLK_F15: printf("<F15>"); break;
         case SDLK_F16: printf("<F16>"); break;
         case SDLK_F17: printf("<F17>"); break;
         case SDLK_F18: printf("<F18>"); break;
         case SDLK_F19: printf("<F19>"); break;
         case SDLK_F20: printf("<F20>"); break;
         case SDLK_F21: printf("<F21>"); break;
         case SDLK_F22: printf("<F22>"); break;
         case SDLK_F23: printf("<F23>"); break;
         case SDLK_F24: printf("<F24>"); break;
         case SDLK_HOME: printf("<home>"); break;
         case SDLK_INSERT: printf("<insert>"); break;
         case SDLK_KP_0: printf("0"); break;
         case SDLK_KP_1: printf("1"); break;
         case SDLK_KP_2: printf("2"); break;
         case SDLK_KP_3: printf("3"); break;
         case SDLK_KP_4: printf("4"); break;
         case SDLK_KP_5: printf("5"); break;
         case SDLK_KP_6: printf("6"); break;
         case SDLK_KP_7: printf("7"); break;
         case SDLK_KP_8: printf("8"); break;
         case SDLK_KP_9: printf("9"); break;
         case SDLK_KP_DIVIDE: printf("/"); break;
         case SDLK_KP_ENTER: printf("<enter>"); break;
         case SDLK_KP_MINUS: printf("-"); break;
         case SDLK_KP_MULTIPLY: printf("*"); break;
         case SDLK_KP_PERIOD: printf("."); break;
         case SDLK_KP_PLUS: printf("+"); break;
         case SDLK_LALT: printf("<l alt>"); break;
         case SDLK_LCTRL: printf("<l ctrl>"); break;
         case SDLK_LEFT: printf("<left arrow>"); break;
         case SDLK_LEFTBRACKET: printf("["); break;
         case SDLK_LGUI: printf("<l gui>"); break;
         case SDLK_LSHIFT: printf("<l shift>"); break;
         case SDLK_MINUS: printf("-"); break;
         case SDLK_NUMLOCKCLEAR: printf("<numlock>"); break;
         case SDLK_PAGEDOWN: printf("<page down>"); break;
         case SDLK_PAGEUP: printf("<page up>"); break;
         case SDLK_PAUSE: printf("<pause>"); break;
         case SDLK_PERIOD: printf("."); break;
         case SDLK_PRINTSCREEN: printf("<print screen>"); break;
         case SDLK_QUOTE: printf("'"); break;
         case SDLK_RALT: printf("<r alt>"); break;
         case SDLK_RCTRL: printf("<r ctrl>"); break;
         case SDLK_RETURN: printf("<return>"); break;
         case SDLK_RETURN2: printf("<return2>"); break;
         case SDLK_RGUI: printf("<r gui>"); break;
         case SDLK_RIGHT: printf("<right arrow>"); break;
         case SDLK_RIGHTBRACKET: printf("]"); break;
         case SDLK_RSHIFT: printf("<r shift>"); break;
         case SDLK_SCROLLLOCK: printf("<scroll lock>"); break;
         case SDLK_SEMICOLON: printf(";"); break;
         case SDLK_SLASH: printf("/"); break;
         case SDLK_SPACE: printf("<space>"); break;
         case SDLK_TAB: printf("<tab>"); break;
         case SDLK_UP: printf("<up arrow>"); break;
         case SDLK_AC_BACK:
         case SDLK_AC_BOOKMARKS:
         case SDLK_AC_FORWARD:
         case SDLK_AC_HOME:
         case SDLK_AC_REFRESH:
         case SDLK_AC_SEARCH:
         case SDLK_AC_STOP:
         case SDLK_AGAIN:
         case SDLK_ALTERASE:
         case SDLK_APPLICATION:
         case SDLK_AUDIOMUTE:
         case SDLK_AUDIONEXT:
         case SDLK_AUDIOPLAY:
         case SDLK_AUDIOPREV:
         case SDLK_AUDIOSTOP:
         default:
            printf("unknown key event");
            break;
      }
      std::fflush(stdout);
   }
};
#endif // GOON_KEYBOARD_HPP

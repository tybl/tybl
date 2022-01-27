// License: The Unlicense (https://unlicense.org)
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <stdio.h>

// A group of buttons, 'q', 'w', 'e'..
class MyButtonGroup : public Fl_Group {
  Fl_Button* butts[3]; // for sake of example, 3 buttons
  static void Button_CB(Fl_Widget* w, void*) {
    Fl_Button* b = (Fl_Button*)w;
    fprintf(stderr, "Button '%s' was %s\n", b->label(), b->value() ? "Pushed" : "Released");
  }

public:
  MyButtonGroup(int X, int Y, int W, int H, const char* L = 0)
    : Fl_Group(X, Y, W, H, L) {
    // Create the three 'q','w','e' buttons
    // The button's label() determines which will keyboard key invokes its callback
    //
    box(FL_BORDER_BOX);
    color(46); // dark bg color for group
    Fl_Button* b;
    int i = 0;
    b = new Fl_Button(x() + 10 + 0, y() + 10, 25, 25, "q");
    b->callback(Button_CB);
    butts[i++] = b;
    b = new Fl_Button(x() + 10 + 50, y() + 10, 25, 25, "w");
    b->callback(Button_CB);
    butts[i++] = b;
    b = new Fl_Button(x() + 10 + 100, y() + 10, 25, 25, "e");
    b->callback(Button_CB);
    butts[i++] = b;
    end();
  }
  int handle(int e) {
    int ret = Fl_Group::handle(e); // assume the buttons won't handle the keyboard events
    switch (e) {
      case FL_FOCUS:
      case FL_UNFOCUS:
        ret = 1; // enables receiving keyboard events
        break;
      case FL_SHORTCUT: // incase widget that isn't ours has focus
      case FL_KEYDOWN:  // keyboard key pushed
      case FL_KEYUP:    // keyboard key released
      {
        // Walk button array, trying to match button's label with the keyboard event.
        // If found, set that button's value() based on up/down event,
        // and invoke that button's callback()
        //
        for (int t = 0; t < 3; t++) {
          Fl_Button* b = butts[t];
          if (Fl::event_key() == b->label()[0]) {                    // event matches button's label?
            b->take_focus();                                         // move focus to this button
            b->value((e == FL_KEYDOWN || e == FL_SHORTCUT) ? 1 : 0); // change the button's state
            b->do_callback();                                        // invoke the button's callback
            ret = 1;                                                 // indicate we handled it
          }
        }
        break;
      }
    }
    return (ret);
  }
};

int main(int, char*[]) {
  Fl_Window* win = new Fl_Window(200, 200, "Example");
  new MyButtonGroup(10, 50, 200 - 20, 200 - 60);
  win->begin();
  (new Fl_Button(10, 10, 25, 25, "X"))
      ->tooltip(
          "This is an extra button outside group "
          "to test focus taken from other buttons");
  win->end();
  win->show();
  return (Fl::run());
}

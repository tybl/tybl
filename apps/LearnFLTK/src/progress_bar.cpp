// License: The Unlicense (https://unlicense.org)
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Window.H>
#include <stdio.h>

// Demonstrate progress bar in app window (windows|linux)
// erco 05/02/05

#ifdef _WIN32
// WINDOWS
#include <windows.h>
#define usleep(v) Sleep(v / 1000)
#else
// UNIX
#include <unistd.h> // usleep
#endif

// Button callback
void butt_cb(Fl_Widget* butt, void* data) {
  // Deactivate the button
  butt->deactivate(); // prevent button from being pressed again
  Fl::check();        // give fltk some cpu to gray out button
  // Make the progress bar
  Fl_Window* w = (Fl_Window*)data; // access parent window
  w->begin();                      // add progress bar to it..
  Fl_Progress* progress = new Fl_Progress(10, 50, 200, 30);
  progress->minimum(0); // set progress range to be 0.0 ~ 1.0
  progress->maximum(1);
  progress->color(0x88888800);           // background color
  progress->selection_color(0x4444ff00); // progress bar color
  progress->labelcolor(FL_WHITE);        // percent text color
  w->end();                              // end adding to window
  // Computation loop..
  for (int t = 1; t <= 500; t++) {
    progress->value(t / 500.0); // update progress bar with 0.0 ~ 1.0 value
    char percent[10];
    sprintf(percent, "%d%%", int((t / 500.0) * 100.0));
    progress->label(percent); // update progress bar's label
    Fl::check();              // give fltk some cpu to update the screen
    usleep(1000);             // 'your stuff' that's compute intensive
  }
  // Cleanup
  w->remove(progress); // remove progress bar from window
  delete (progress);   // deallocate it
  butt->activate();    // reactivate button
  w->redraw();         // tell window to redraw now that progress removed
}
// Main
int main() {
  Fl_Window win(220, 90);
  Fl_Button butt(10, 10, 100, 25, "Press");
  butt.callback(butt_cb, &win);
  win.resizable(win);
  win.show();
  return (Fl::run());
}

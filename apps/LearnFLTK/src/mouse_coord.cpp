#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>
#include <FL/fl_draw.H>
#include <stdio.h>
// Demonstrate drawing mouse coords:
//      o w/out redrawing entire screen
//      o w/out using overlay planes or windows
//      o w/out using XOR mode
class MyDesk : public Fl_Group {
protected:
    int handle(int e) {
        int ret = Fl_Group::handle(e);
        switch ( e ) {
            case FL_ENTER:
                ret = 1;                // FL_ENTER: must return(1) to receive FL_MOVE
                break;
            case FL_MOVE:               // FL_MOVE: mouse movement causes 'user damage' and redraw..
                damage(FL_DAMAGE_USER1);
                ret = 1; 
                break;
        }
        return(ret);
    }
    // Draw mouse coords in small black rectangle
    void draw_coords() {
        // Coordinates as a string
        char s[80];
        sprintf(s, "x=%d y=%d", (int)Fl::event_x(), (int)Fl::event_y());
        // Black rect
        fl_color(FL_BLACK);
        fl_rectf(10,10,200,25);
        // White text
        fl_color(FL_WHITE);
        fl_font(FL_HELVETICA, 18);
        fl_draw(s, 15, 25);
    }
    void draw() {
        // User damage ONLY? just draw coords and done
        if ( damage() == FL_DAMAGE_USER1 ) {
            draw_coords();
            return;
        }
        // Let group draw itself
        Fl_Group::draw(); 
        {
            // Show redraw count, so we can tell when full redraws occur.
            static int redraws = 0;
            char s[80]; sprintf(s, "redraw #%d", ++redraws);
            fl_color(FL_BLACK);
            fl_font(FL_COURIER, 80);
            fl_draw(s, 50, h()/2);
        }
        // Draw coords last
        draw_coords();
    }
public:
    MyDesk(int X, int Y, int W, int H, const char *L=0) : Fl_Group(X,Y,W,H,L) {
        color(48);
    }
};

/// MAIN
int main() {
    Fl_Window win(720,486);
    MyDesk desk(10,10,700,466);
    win.resizable(win);
    win.show();
    return(Fl::run());
}

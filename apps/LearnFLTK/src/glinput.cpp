// License: The Unlicense (https://unlicense.org)
#include <stdio.h>  /* I/O lib         ISOC  */
#include <stdlib.h> /* Standard Lib    ISOC  */

#include <FL/Fl.H>           /* FLTK main       FLTK  */
#include <FL/Fl_Box.H>       /* FLTK box        FLTK  */
#include <FL/Fl_Button.H>    /* FLTK button     FLTK  */
#include <FL/Fl_Gl_Window.H> /* FLTK OpenGL     FLTK  */
#include <FL/Fl_Window.H>    /* FLTK window     FLTK  */
#include <FL/gl.h>           /* FLTK OpenGL     FLTK  */
#include <FL/glu.h>          /* FLTK OpenGL     FLTK  */
#include <FL/glut.H>         /* FLTK GLUT       FLTK  */

#ifdef __APPLE__
#include <OpenGL/glu.h> /* Open GL Stuff   APPLE */
#else
#include <GL/glu.h> /* Open GL Stuff   Linux */
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class myGLwindow : public Fl_Gl_Window {
  void computeCurve();
  int handle(int event);
  void draw();

public:
  myGLwindow(int x, int y, int w, int h, const char* l = 0)
    : Fl_Gl_Window(x, y, w, h, l) {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void myGLwindow::draw() {
  if (!valid()) { // valid() is magic set after first draw() call.
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, 1, 10, 120);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 50, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glScalef(.3, .3, .3);

    computeCurve();
  }
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glCallList(1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int myGLwindow::handle(int event) {
  static int x, y;
  static float rx, ry;
  switch (event) {
    case FL_PUSH:
      // mouse down pos in Fl::event_x() and Fl::event_y()
      x = Fl::event_x();
      y = Fl::event_y();
      return 1;
    case FL_DRAG: {
      int cx = Fl::event_x();
      int cy = Fl::event_y();
      if (abs(x - cx) < 100 && abs(y - cy) < 100) {
        rx += -(x - cx) * 0.5;
        ry += -(y - cy) * 0.5;

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 0, 50, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glScalef(.3, .3, .3);
        glRotatef(ry, 1, 0, 0);
        glRotatef(rx, 0, 1, 0);
        redraw();
      }
      x = cx;
      y = cy;
    }
      return 1;
    case FL_RELEASE: return 1;
    case FL_FOCUS: return 1;   // return 1 to get keyboard events
    case FL_UNFOCUS: return 1; // Return 1 to get keyboard events
    case FL_KEYBOARD:
      // key in Fl::event_key(), ascii in Fl::event_text()
      printf("Key: %s\n", Fl::event_text());
      return 0; // return 1 input was understood
    case FL_SHORTCUT:
      // key in Fl::event_key(), ascii in Fl::event_text()
      return 0; // return 1 input was understood
    default: return 1;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void myGLwindow::computeCurve() {
  int maxBalls = 5000;
  double tDelta = 0.01;
  double x = 0.11;
  double y = 0.0;
  double z = 0;
  double a = 10;
  double b = 28;
  double c = 8.0 / 3.0;
  int numBalls;
  double xNew, yNew, zNew;

  glNewList(1, GL_COMPILE);
  glColor3f(1, 1, 1);
  glPointSize(1.0);
  glBegin(GL_LINE_STRIP);
  for (numBalls = 0; numBalls < maxBalls; numBalls++) {
    xNew = x + a * (y - x) * tDelta;
    yNew = y + (x * (b - z) - y) * tDelta;
    zNew = z + (x * y - c * z) * tDelta;
    glColor3f(1.0 * numBalls / maxBalls, 0.2, 1.0 - numBalls / maxBalls);
    glVertex3f(xNew, yNew, zNew);
    x = xNew;
    y = yNew;
    z = zNew;
  }
  glEnd();

  // Draw the x/y/z axis
  glBegin(GL_LINE_STRIP);
  glColor3f(1, 0, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(40, 0, 0);
  glVertex3f(0, 0, 0);
  glColor3f(0, 1, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 40, 0);
  glVertex3f(0, 0, 0);
  glColor3f(0, 0, 1);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 40);
  glEnd();

  // Draw the box
  glBegin(GL_LINE_STRIP);
  glColor3f(1, 1, 1);
  glVertex3f(40, -40, -40);
  glVertex3f(40, 40, -40);
  glVertex3f(-40, 40, -40);
  glVertex3f(-40, -40, -40);
  glVertex3f(40, -40, -40);

  glVertex3f(40, -40, 40);
  glVertex3f(40, 40, 40);
  glVertex3f(-40, 40, 40);
  glVertex3f(-40, -40, 40);
  glVertex3f(40, -40, 40);

  glVertex3f(40, 40, 40);
  glVertex3f(40, 40, -40);

  glVertex3f(-40, 40, -40);
  glVertex3f(-40, 40, 40);

  glVertex3f(-40, -40, 40);
  glVertex3f(-40, -40, -40);

  glEnd();

  glEndList();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
  myGLwindow theGLwin(50, 50, 500, 500, "Interactive Lorenz Demo Program");
  theGLwin.show();

  return Fl::run();
}

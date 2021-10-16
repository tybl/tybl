#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>

const int window_height = 180;
const int window_width = 290;

const int b_padding = 3;
const int b_x = 20;
const int b_y = 140;

const int b_num_height = 24;
const int b_num_width = 48;

const int b_eq_height = b_num_height * 2 + b_padding;
const int b_eq_width = 48;

const int input_x = 20;
const int input_y = 20;
const int input_height = 30;

int inp_step = 0, dotted = 0;
long double first_num = 0;

char calc_op[2] = {0};
Fl_Input *input;


void ac_b_click()
{
  input->value("0");
  inp_step = 0;
  dotted = 0;
  calc_op[0] = 0;
}

int eq_b_click()
{
  if (inp_step == 0) {
    return 0;
  }
  int other_div = 0;
  long double result;
  long double second_num = atof(input->value());

  switch (calc_op[0]) {
    case '+': result = first_num + second_num; break;
    case '-': result = first_num - second_num; break;
    case '*': result = first_num * second_num; break;
    case '/':
      if (first_num == 0 && second_num == 0) {
        other_div = 1;
        input->value("nan");
      } else if (second_num == 0) {
        other_div = 1;
        input->value("inf");
      } else {
        result = first_num / second_num;
      }
      break;
    default:
      return 0;
  }
  if (other_div == 0) {
    char bufer[128];

    sprintf(bufer, "%.12Lf", (long double)result);

    // removing extra zeros
    int i;
    for (i = strlen(bufer) - 1; i > 0 && bufer[i] == '0'; i--) {
      bufer[i] = '\0';
    }
    if (bufer[i] == '.') {
      bufer[i] = '\0';
    }

    input->value(bufer);
  }
  inp_step = 0;
  first_num = 0;
  return 1;
}

int num_b_click(Fl_Button *button, void* = 0)
{
  if (inp_step == 0 || inp_step == 2 || strcmp(input->value(), "0") == 0) {
    input->value("");
    inp_step++;
  }

  char str[128] = {0};
  strcat(str, input->value());
  strcat(str, button->label());
  input->value(str);
  return 1;
}

void do_b_click(Fl_Button *button, void* = 0)
{
  if (inp_step == 3) {
    eq_b_click();
  }
  first_num = atof(input->value());
  calc_op[0] = (char)*button->label();
  inp_step = 2;
  dotted = 0;
}

void dot_b_click(Fl_Button*, void* = 0)
{
  if (inp_step == 0 || inp_step == 2) {
    input->value("0.");
    dotted = 1;
    inp_step = 1;
    return;
  }
  if (dotted != 1) {
    dotted = 1;
    char str[128] = {0};
    strcat(str, input->value());
    strcat(str, ".");
    input->value(str);
  }
}

int main(int argc, char **argv)
{
  // Make the app window
  Fl_Window *window = new Fl_Window(window_width, window_height);
  // Give the window a name.
  // TODO: Can't we create the window object and give it a name at the same time?
  window->label("Calculator");

  int button_x = b_x;
  int button_y = b_y;

  // Create button for the decimal place
  Fl_Button *button_dot = new Fl_Button(button_x + b_num_width + b_padding, button_y, b_num_width, b_num_height, ".");
  button_dot->callback((Fl_Callback*)dot_b_click);
  button_dot->box(FL_GTK_UP_BOX);

  // create digit button
  Fl_Button *num_b[10];
  char labels[10][2] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
  for (int i = 0, k = 0; i < 10; i++) {
    if (i > 1) {
      button_x += b_padding + b_num_width;
    }
    if (i == 1 || ++k == 3) {
      k = 0;
      button_y -= b_num_height + b_padding;
      button_x = b_x;
    }

    num_b[i] = new Fl_Button(button_x, button_y, b_num_width, b_num_height, labels[i]);
    num_b[i]->callback((Fl_Callback*)num_b_click);
    num_b[i]->box(FL_GTK_UP_BOX);
  }

  // create doing button
  Fl_Button *do_b[4];
  button_x += b_padding + b_num_width;
  button_y = b_y;
  for (int i = 0; i < 4; i++) {
    do_b[i] = new Fl_Button(button_x, button_y, b_num_width, b_num_height);
    do_b[i]->callback((Fl_Callback*)do_b_click);
    do_b[i]->box(FL_GTK_UP_BOX);

    button_y -= b_num_height + b_padding;
  }
  do_b[0]->label("+");
  do_b[1]->label("-");
  do_b[2]->label("*");
  do_b[3]->label("/");

  // create ac button
  button_x += b_padding + b_num_width;

  button_y += b_num_height + b_padding;
  Fl_Button *button_ac = new Fl_Button(button_x, button_y, b_eq_width, b_eq_height, "AC");
  button_ac->callback((Fl_Callback*)ac_b_click);
  button_ac->box(FL_GTK_UP_BOX);

  // create eq button
  button_y += b_eq_height + b_padding;
  Fl_Button *button_eq = new Fl_Button(button_x, button_y, b_eq_width, b_eq_height, "=");
  button_eq->callback((Fl_Callback*)eq_b_click);
  button_eq->box(FL_GTK_UP_BOX);


  // create input
  input = new Fl_Input(input_x, input_y, window_width - (input_x * 2), input_height);
  input->box(FL_GTK_UP_BOX);
  input->textsize(18);
  input->readonly(1);
  input->value("0");


  window->end();
  window->show(argc, argv);
  return Fl::run();
}

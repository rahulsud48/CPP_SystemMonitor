#include "ncurses_display.h"
#include "system.h"

#include<string>
#include<iostream>
using std::string;
using std::cout;

int main() {
  System system;
  // long value = system.UpTime();
  // cout << value << "\n";
  NCursesDisplay::Display(system);
}
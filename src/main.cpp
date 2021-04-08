#include "ncurses_display.h"
#include "system.h"
#include<processor.h>

#include<string>
#include<iostream>
using std::string;
using std::cout;

int main() {
  // Processor processor;
  System system;
  // float value = processor.Utilization();
  // cout << value << "\n";
  NCursesDisplay::Display(system);
}
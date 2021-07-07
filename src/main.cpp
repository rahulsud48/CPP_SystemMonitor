#include "ncurses_display.h"
#include "system.h"
#include<processor.h>
#include<linux_parser.h>

#include<string>
#include<iostream>
using std::string;
using std::cout;

int main() {
  // Processor processor;
  System system;
  // cout<< LinuxParser::UpTime()<<"\n";
  // float value = processor.Utilization();
  // cout << value << "\n";
  NCursesDisplay::Display(system);
}
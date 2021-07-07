#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    int hr, min;

    min = seconds/60;
    hr = min/60;

  string time = string(2 - std::to_string(int(hr)).length(), '0') + std::to_string(int(hr)) + ':' +
                string(2 - std::to_string(int(min%60)).length(), '0') + std::to_string(int(min%60)) + ':' +
                string(2 - std::to_string(seconds%60).length(), '0') + std::to_string(seconds%60);

    return  time;
}
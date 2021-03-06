#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
# include <algorithm>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::stol;
using std::to_string;
using std::vector;
using std::cout;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    if (file->d_type == DT_DIR) {
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  float value;
  string size;

  float totalmemory;
  float freememory;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      while (linestream >> key >> value >> size){
        if (key == "MemTotal:"){
          totalmemory = value;
        }
        if (key == "MemFree:"){
          freememory = value;
        }
      }
    }
  }
  return (totalmemory - freememory)/totalmemory;
}

void LinuxParser::removeCharsFromString( std::string &str, char* charsToRemove ) {
   for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
      str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
   }
}

// TODO: Read and return the system uptime
long int LinuxParser::UpTime() {
  string uptime, idletime, line;
  string uptime2="";
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> idletime;
  }
  long int uptime_ = atol(uptime.c_str());
  return uptime_;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  string line, val, time_u, time_s, time_cu, time_cs;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      for(int j = 1; j < 14; j++) {
        linestream >> val; 
      }
      linestream >> time_u >> time_s >> time_cu >> time_cs; 
      long totaltime = stol(time_u) + stol(time_s) + stol(time_cu) + stol(time_cs);
      return totaltime;
    }
  }
  return 0;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string line;
  string key;
  string v1,v2,v3,v4,v5,v6,v7,v8,v9,v10;
  vector<string> cpu_data{};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      while (linestream>>key>>v1>>v2>>v3>>v4>>v5>>v6>>v7>>v8>>v9>>v10){
        if (key == "cpu"){
          cpu_data = {v1,v2,v3,v4,v5,v6,v7,v8,v9,v10};
          return cpu_data;
        }
      }
    }
  }
  return cpu_data;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line, key;
  int v;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      while (linestream >> key >> v){
        if (key == "processes"){
          return v;
        }
      }
    }
  }
  return 0;
  
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line, key;
  int val;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      while (linestream >> key >> val){
        if (key == "procs_running"){
          return val;
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid){
  string line;
  std::ifstream filestream(kProcDirectory+std::to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()){
    std::getline(filestream, line);
    return line;
  } else{
    return 0;
  }

}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line, key, val;
  int ram;
  std::ifstream filestream(kProcDirectory+std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      while (linestream >> key >> val){
        if (key == "VmSize:"){
          ram = std::stoi(val);
          ram = ram/1024;
          return std::to_string(ram);
        }
      }
    }
  }
  return "0";
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string line, key, val;
  std::ifstream filestream(kProcDirectory+std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      while (linestream >> key >> val){
        if (key == "Uid:"){
          return val;
        }
      }
    }
  }
  return "0";
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string user, key, uid_left, uid_right, line;
  uid_right = LinuxParser::Uid(pid);
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()){
    while (std::getline(filestream, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> user >> key >> uid_left){
        if (uid_left == uid_right ){
          return user;
        }
      }
    }
  }
  return "0";
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::UpTime(int pid) {
  string line, val;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      for (int j; j < 22; j++){
        linestream >> val;
      }
      int upTimePid = UpTime() - std::atol(val.c_str())/sysconf(_SC_CLK_TCK);
      return upTimePid;
    }
  }
  return 0;
}

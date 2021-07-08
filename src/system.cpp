#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;


// TODO: Return the system's CPU

void System::CreateCPU(){
    Processor processor;
    cpu_ = processor;
}

Processor& System::Cpu() {
    System::CreateCPU();
    return cpu_;
}

void System::CreateProcesses(){
    vector<int> pids = LinuxParser::Pids();
    for (int pid : pids) {
        Process new_process(pid);
        if (new_process.Command() == "" || new_process.Ram()==""){
            continue;
        } else {
            processes_.emplace_back(new_process);
        }  
    }  
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
    System::CreateProcesses();
    return processes_; 
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
    string value = LinuxParser::Kernel();
    return value;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() {
    float value = LinuxParser::MemoryUtilization();
    return value;
}

// TODO: Return the operating system name
std::string System::OperatingSystem() {
    string value = LinuxParser::OperatingSystem();
    return value;
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() {
    return LinuxParser::RunningProcesses();
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
    return LinuxParser::TotalProcesses(); 
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() {
    return LinuxParser::UpTime(); 
}
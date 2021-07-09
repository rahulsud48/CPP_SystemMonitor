#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    vector<string> cpu_data = LinuxParser::CpuUtilization();
    float sum = 0;
    int count = 0;
    int idle, iowait;
    float cpu_perc;
    for (unsigned  i = 0; i < cpu_data.size(); i++){
        string s = cpu_data[i];
        int x = 0;
        stringstream ss(s);
        ss >> x;
        if (count == 3){
            idle = x;
        }
        if (count == 4){
            iowait = x;
        }
        sum += x;
        count++;
    }
    // cout << sum << "\n";
    // cout << iowait << "\n";
    // cout << idle << "\n";
    cpu_perc = (sum - iowait - idle)/sum;
    // cout << cpu_perc << "\n";
    return cpu_perc;
}
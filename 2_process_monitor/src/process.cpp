#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include <iostream>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Return this process's ID
int Process::Pid() { return this->pid; }

/*
Source: https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
*/
// Return this process's CPU utilization
float Process::CpuUtilization() const { 
    long sys_uptime = LinuxParser::UpTime();

    string value;
    string line;
    std::vector<std::string> stat;
    std::ifstream stream(LinuxParser::kProcDirectory + "/" + to_string(this->pid) + LinuxParser::kStatFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            for (uint i = 0; i < 22 && linestream >> value; i++) {
                stat.emplace_back(value);
            }
        }
    }

    long utime = std::stol(stat[13]);
    long stime = std::stol(stat[14]);
    long cutime = std::stol(stat[15]);
    long cstime = std::stol(stat[16]);
    long starttime = std::stol(stat[21]);
    long total_time = utime + stime + cutime + cstime;
    long seconds = sys_uptime - (starttime / sysconf(_SC_CLK_TCK));

    return (1.0*(total_time / sysconf(_SC_CLK_TCK)) / seconds);
}

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(this->pid); }

// Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(this->pid); }

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(this->pid); }

// Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(this->pid); }

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& other) const { 
    return this->CpuUtilization() < other.CpuUtilization(); 
}

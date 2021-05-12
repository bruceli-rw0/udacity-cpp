#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

/*
PRETTY_NAME=
    A pretty operating system name in a format suitable for presentation to the 
    user. May or may not contain a release code name or OS version of some kind, 
    as suitable. If not set, defaults to "PRETTY_NAME="Linux"". 
    Example: "PRETTY_NAME="Fedora 17 (Beefy Miracle)"".
*/
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
            // init: PRETTY NAME="Ubuntu 16.04.5 LTS"
            // key: PRETTY_NAME
            // value: Ubuntu_16.04.5_LTS
            while (linestream >> key >> value) {
                if (key == "PRETTY_NAME") {
                    std::replace(value.begin(), value.end(), '_', ' ');
                    return value;
                }
            }
        }
    }
    filestream.close();
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
    stream.close();
    return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
    vector<int> pids;
    DIR* directory = opendir(kProcDirectory.c_str());
    struct dirent* file;
    while ((file = readdir(directory)) != nullptr) {
        // Is this a directory?
        if (file->d_type == DT_DIR) {
            // Is every character of the name a digit?
            string filename(file->d_name);
            if (std::all_of(filename.begin(), filename.end(), isdigit)) {
                int pid = stoi(filename);
                pids.emplace_back(pid);
            }
        }
    }
    closedir(directory);
    return pids;
}

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{ 
    string line;
    string key;
    double value = 0.0;
    double mem_total = 0.0;
    double mem_free = 0.0;
    std::ifstream stream(kProcDirectory + kMeminfoFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "MemTotal") {
                    mem_total = value;
                } else if (key == "MemFree") {
                    mem_free = value;
                }
            }
        }
    }
    stream.close();
    return (mem_total - mem_free) / mem_total; 
}

// Read and return the system uptime
long LinuxParser::UpTime() 
{ 
    double up_time = 0.0;
    double time_in_idle = 0.0;
    string line;
    std::ifstream stream(kProcDirectory + kUptimeFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            if (linestream >> up_time >> time_in_idle) {
                return (long) up_time;
            }
        }
    }
    stream.close();
    return (long) up_time; 
}

/*
// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }
*/

// Read and return CPU utilization
vector<long> LinuxParser::CpuUtilization() 
{
    vector<long> stat;
    string line;
    string key;
    long value = 0;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            if (linestream >> key) {
                if (key == "cpu") {
                    for (uint i = 0; i < 10 && linestream >> value; i++) {
                        stat.emplace_back(value);
                    }
                }
            }
        }
    }
    return std::move(stat);
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{ 
    string line;
    string key;
    int value = 0;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "processes") {
                    return value;
                }
            }
        }
    }
    stream.close();
    return value; 
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{
    string line;
    string key;
    int value = 0;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "procs_running") {
                    return value;
                }
            }
        }
    }
    stream.close();
    return value; 
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) 
{ 
    string line;
    string value;
    std::ifstream stream(kProcDirectory + "/" + to_string(pid) + kCmdlineFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            while (linestream >> value) {
                return value;
            }
        }
    }
    stream.close();
    return string(); 
}

/*
Use VmData instead of VmSize since VmSize is the sum of all the virtual memory.
Whereas VmData gives the exact physical memory being used as a part of Physical RAM. 
*/
// Read and return the memory used by a process
string LinuxParser::Ram(int pid) 
{ 
    string line;
    string key;
    string value;
    std::ifstream stream(kProcDirectory + "/" + to_string(pid) + kStatusFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "VmData") {
                    return to_string(std::stol(value) / 1000);
                }
            }
        }
    }
    stream.close();
    return string(); 
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) 
{ 
    string line;
    string key;
    string value;
    std::ifstream stream(kProcDirectory + "/" + to_string(pid) + kStatusFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "Uid") {
                    return value;
                }
            }
        }
    }
    stream.close();
    return string(); 
}

// Read and return the user associated with a process
string LinuxParser::User(int pid) 
{ 
    string uid = Uid(pid);
    string line;
    string key;
    string c;
    string value;
    std::ifstream stream(kPasswordPath);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> c >> value) {
                if (value == uid) {
                    return key;
                }
            }
        }
    }
    stream.close();
    return string(); 
}

// Read and return the uptime of a process
long LinuxParser::UpTime(int pid) 
{ 
    long sys_uptime = UpTime();

    string value;
    string line;
    std::ifstream stream(kProcDirectory + "/" + to_string(pid) + kStatFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            for (uint i = 0; i < 22 && linestream >> value; i++) {}
        }
    }
    stream.close();
    return (long) (sys_uptime - std::stol(value) / sysconf(_SC_CLK_TCK)); 
}

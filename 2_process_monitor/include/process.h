#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
public:
    Process(int pid_) : pid(pid_) {}
    int Pid();
    std::string User();
    std::string Command();
    float CpuUtilization() const;
    std::string Ram();
    long int UpTime();
    bool operator<(Process const& a) const;

private:
    int pid;
};

#endif

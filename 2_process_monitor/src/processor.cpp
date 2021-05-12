#include "processor.h"
#include "linux_parser.h"

#include <iostream>
#include <sstream>
#include <numeric>
#include <string>
using std::string;
using std::accumulate;

/*

stat
(0) user
(1) nice
(2) system
(3) idle
(4) iowait
(5) irq
(6) softirq
(7) steal
(8) guest
(9) guest_nice

CPU Usage calculation:

(1) PrevIdle = prev_idle + prev_iowait
(2) Idle = idle + iowait

(3) PrevNonIdle = pre_vuser + prev_nice + prev_system + prev_irq + prev_softirq + prev_steal
(4) NonIdle = user + nice + system + irq + softirq + steal

(5) PrevTotal = PrevIdle + PrevNonIdle
(6) Total = Idle + NonIdle

# differentiate: actual value minus the previous one
(7) totald = Total - PrevTotal
(8) idled = Idle - PrevIdle

(9) CPU_Percentage = (totald - idled)/totald

Source: https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux

*/

// Return the aggregate CPU utilization
float Processor::Utilization() { 
    // update the previous stat before reading new stat
    this->prev_stat.swap(this->stat);
    this->stat = LinuxParser::CpuUtilization();

    long prev_idle = this->prev_stat[3] + this->prev_stat[4];
    long idle = this->stat[3] + this->stat[4];
    long prev_total = accumulate(this->prev_stat.begin(), this->prev_stat.begin() + 8, 0);
    long total = accumulate(this->stat.begin(), this->stat.begin() + 8, 0);
    long diff_total = total - prev_total;
    long diff_idle = idle - prev_idle;

    // std::cout << "\n\n";
    // std::cout << "Prev Total: " << prev_total << "\n";
    // std::cout << "Total: " << total << "\n";
    // std::cout << "Diff Total: " << diff_total << "\n";
    // std::cout << "CPU usage: " << (diff_total - diff_idle) / diff_total << "\n";
    // std::cout << "\n";

    return 1.0*(diff_total - diff_idle) / diff_total;
}

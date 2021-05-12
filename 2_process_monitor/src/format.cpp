#include <string>

#include <iomanip>
#include <sstream>
#include <chrono>

#include "format.h"

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{
    string hour = std::to_string((long) seconds / 3600);
    string minute = std::to_string((long) (seconds%3600) / 60);
    string second = std::to_string((long) (seconds%3600) % 60);

    if (hour.length() == 1) hour = "0" + hour;
    if (minute.length() == 1) minute = "0" + minute;
    if (second.length() == 1) second = "0" + second;

    string output = hour + ":";
    output += minute + ":";
    output += second;
    return output; 
}

// Alternative solution by Udacity mentor
string Format::ElapsedTimeAlt(long s) 
{
    std::chrono::seconds seconds{s};

    // return std::chrono::format("%T", seconds); // in C++20 :-)

    std::chrono::hours hours =
        std::chrono::duration_cast<std::chrono::hours>(seconds);

    seconds -= std::chrono::duration_cast<std::chrono::seconds>(hours);

    std::chrono::minutes minutes =
        std::chrono::duration_cast<std::chrono::minutes>(seconds);

    seconds -= std::chrono::duration_cast<std::chrono::seconds>(minutes);

    std::stringstream ss{};

    ss << std::setw(2) << std::setfill('0') << hours.count()     // HH
       << std::setw(1) << ":"                                    // :
       << std::setw(2) << std::setfill('0') << minutes.count()   // MM
       << std::setw(1) << ":"                                    // :
       << std::setw(2) << std::setfill('0') << seconds.count();  // SS

    return ss.str();
}

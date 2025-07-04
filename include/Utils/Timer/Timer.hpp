#ifndef UTILS_TIMER_TIMER_HPP
#define UTILS_TIMER_TIMER_HPP

#include <chrono>

class Timer {
    std::chrono::high_resolution_clock::time_point begin, end;

    std::chrono::high_resolution_clock::time_point now() const;
public:
    void start();
    void stop();
    long long duration() const;
};

#endif
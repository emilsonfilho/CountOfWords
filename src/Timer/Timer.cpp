#include "Utils/Timer/Timer.hpp"

std::chrono::high_resolution_clock::time_point Timer::now() const {
    return std::chrono::high_resolution_clock::now();
}

void Timer::start() {
    begin = now();
}

void Timer::stop() {
    end = now();
}

std::chrono::milliseconds Timer::duration() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
}
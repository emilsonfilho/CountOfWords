#ifndef UTILS_TIMER_TIMER_HPP
#define UTILS_TIMER_TIMER_HPP

#include <chrono>

/**
 * @class Timer
 * @brief A utility class for measuring time intervals using high-resolution clock.
 * 
 * This class provides functionality to start, stop, and calculate the duration
 * of time intervals. It uses `std::chrono::high_resolution_clock` for precise
 * time measurements.
 */
class Timer {
    std::chrono::high_resolution_clock::time_point begin, end;

    std::chrono::high_resolution_clock::time_point now() const;
public:
    /**
     * @brief Starts the timer.
     * 
     * This function initializes or resets the timer to begin tracking elapsed time.
     */
    void start();

    /**
     * @brief Stops the timer and records the elapsed time.
     * 
     * This function halts the timer.
     */
    void stop();

    /**
     * @brief Retrieves the duration measured by the timer.
     * 
     * @return The duration in milliseconds as a long long integer.
     */
    std::chrono::milliseconds duration() const;
};

#endif
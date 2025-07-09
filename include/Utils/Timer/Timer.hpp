#ifndef UTILS_TIMER_TIMER_HPP
#define UTILS_TIMER_TIMER_HPP

#include <chrono>
#include <string>

/**
 * @class Timer
 * @brief A utility class for measuring time intervals using high-resolution
 * clock.
 *
 * This class provides functionality to start, stop, and calculate the duration
 * of time intervals. It uses `std::chrono::high_resolution_clock` for precise
 * time measurements.
 */
class Timer {
  std::chrono::high_resolution_clock::time_point begin, end;

  /**
   * @brief Returns the current time point using high-resolution clock.
   *
   * @return std::chrono::high_resolution_clock::time_point The current time
   * point.
   */
  std::chrono::high_resolution_clock::time_point now() const;

public:
  /**
   * @brief Starts the timer.
   *
   * This function initializes or resets the timer to begin tracking elapsed
   * time.
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

  /**
   * @brief Gets the current system date and time as a localized string.
   * @note The output is formatted as "Weekday, DD of Month of YYYY - HH:MM:SS" 
   * using the application's configured locale.
   * @return A string containing the formatted current date and time.
   */
  static std::string getCurrentDateTime();
};

#endif
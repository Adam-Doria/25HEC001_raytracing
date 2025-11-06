#pragma once

#include <chrono>
#include <string>

/**
 * @brief Simple timing helper to measure elapsed time.
 *
 * Usage:
 * @code
 * Chrono timer;
 * timer.start();
 * double s = timer.stop();
 * timer.log("Elapsed");
 * @endcode
 */
class Chrono {
public:
    /** @brief Start the timer. Records the current time internally. */
    void start();

    /**
     * @brief Stop the timer and return the elapsed time in seconds.
     * @return Elapsed time in seconds as a double.
     */
    double stop();

    /**
     * @brief Stop the timer and print a message to stdout with the elapsed time.
     * @param message Message prefix printed before the measured seconds.
     */
    void log(const std::string& message = "Temps écoulé");

private:
    std::chrono::steady_clock::time_point start_time;  ///< Start time point
};

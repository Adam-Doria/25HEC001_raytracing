#ifndef CHRONO_TIMER_HPP
#define CHRONO_TIMER_HPP

#include <chrono>
#include <string>

class Chrono {
public:
    void start();
    double stop();
    void log(const std::string& message = "Temps écoulé");

private:
    std::chrono::steady_clock::time_point start_time;
};

#endif

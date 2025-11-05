#include "chrono_timer.hpp"

#include <iomanip>
#include <iostream>

void Chrono::start() {
    start_time = std::chrono::steady_clock::now();
}

double Chrono::stop() {
    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    return elapsed.count();
}

void Chrono::log(const std::string& message) {
    std::cout << message << " : " << std::fixed << std::setprecision(6) << stop() << " s\n";
}

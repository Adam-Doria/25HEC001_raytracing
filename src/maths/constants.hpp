#pragma once

#include <cstdlib>
#include <limits>
#include <random>

// Mathematical Constants
inline constexpr double infinity = std::numeric_limits<double>::infinity();
inline constexpr double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline float random_float() {
    thread_local static std::mt19937* generator = nullptr;
    if (!generator) {
        std::random_device rd;
        generator = new std::mt19937(rd());
    }
    thread_local static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    return distribution(*generator);
}

inline float random_float(float min, float max) {
    return min + (max - min) * random_float();
}

inline int random_int(int min, int max) {
    return int(random_float(min, max + 1));
}
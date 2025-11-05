#pragma once

#include <limits>

// Mathematical Constants
inline constexpr double infinity = std::numeric_limits<double>::infinity();
inline constexpr double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline float random_float() {
    return rand() / (RAND_MAX + 1.0f);
}

inline float random_float(float min, float max) {
    return min + (max - min) * random_float();
}
#pragma once

#include "constants.hpp"

class interval {
public:
    float min;
    float max;

    interval() : min(+infinity), max(-infinity) {}
    interval(float min, float max) : min(min), max(max) {}

    float size() const {
        return max - min;
    }

    bool contains(float value) const {
        return value >= min && value <= max;
    }

    bool surrounds(const interval& other) const {
        return (min <= other.min) && (max >= other.max);
    }

    bool overlaps(const interval& other) const {
        return (min <= other.max) && (other.min <= max);
    }

    float clamp(float value) const {
        if (value < min)
            return min;
        if (value > max)
            return max;
        return value;
    }

    interval expand(float delta) const {
        float padding = delta * 0.5f;
        return interval(min - padding, max + padding);
    }

    interval(const interval& a, const interval& b) {
        min = (a.min <= b.min) ? a.min : b.min;
        max = (a.max >= b.max) ? a.max : b.max;
    }

    static const interval empty, universe;
};

inline const interval interval::empty = interval(+infinity, -infinity);
inline const interval interval::universe = interval(-infinity, +infinity);
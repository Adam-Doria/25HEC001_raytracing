#pragma once

#include "maths/vector3.hpp"

class ray {
public:
    ray() {}

    ray(const point3& origin, const vector3& direction) : orig(origin), dir(direction) {}

    const point3& origin() const {
        return orig;
    }
    const vector3& direction() const {
        return dir;
    }

    point3 at(float t) const {
        return orig + t * dir;
    }

private:
    point3 orig;
    vector3 dir;
};

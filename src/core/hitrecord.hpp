#pragma once

#include "core/ray.hpp"
#include "maths/vector3.hpp"

class HitRecord {
public:
    point3 p;
    vector3 normal;
    float t;
    bool front_face;

    void set_face_normal(const ray& r, const vector3& outward_normal);
};

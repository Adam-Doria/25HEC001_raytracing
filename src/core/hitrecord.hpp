#pragma once

#include "lib/lib.hpp"

class material;

class HitRecord {
public:
    point3 p;
    vector3 normal;
    shared_ptr<material> mat;
    float t;
    bool front_face;

    void set_face_normal(const ray& r, const vector3& outward_normal);
};

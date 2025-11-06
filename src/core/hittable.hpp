#pragma once

#include "aabb.hpp"

class ray;
struct HitRecord;
class interval;

class Hittable {
public:
    virtual ~Hittable() noexcept = default;
    virtual bool hit(const ray& r, interval ray_t, HitRecord& rec) const = 0;
    virtual aabb bounding_box() const = 0;
};

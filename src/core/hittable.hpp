#pragma once

class ray;
struct HitRecord;
class interval;

class Hittable {
public:
    virtual ~Hittable() noexcept = default;
    virtual bool hit(const ray& r, interval ray_t, HitRecord& rec) const = 0;
};

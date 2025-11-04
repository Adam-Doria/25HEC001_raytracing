#pragma once

class ray;
struct HitRecord;

class Hittable {
public:
    virtual ~Hittable() noexcept = default;
    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const = 0;
};

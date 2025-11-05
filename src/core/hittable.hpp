#pragma once

class ray;
struct HitRecord;

class Hittable {
public:
    virtual ~Hittable() noexcept = default;
    virtual bool hit(const ray& r, float ray_tmin, float ray_tmax, HitRecord& rec) const = 0;
};

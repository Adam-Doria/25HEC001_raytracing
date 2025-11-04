#pragma once

class ray;
class HitRecord;

#include "hittable/hittable.hpp"
#include "maths/vector3.hpp"

class sphere : public Hittable {
public:
    sphere(const point3& center, double radius);

    bool hit(const ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const override;

private:
    point3 center;
    double radius;
};

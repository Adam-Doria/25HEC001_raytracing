#include "sphere.hpp"

#include <algorithm>
#include <cmath>

#include "core/ray.hpp"
#include "hitrecord/hitrecord.hpp"
#include "maths/vector3.hpp"

sphere::sphere(const point3& center, double radius)
    : center(center), radius(std::max(1e-9, radius)) {}

bool sphere::hit(const ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const {
    vector3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return false;
    auto sqrtd = std::sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (root < ray_tmin || root > ray_tmax) {
        root = (-half_b + sqrtd) / a;
        if (root < ray_tmin || root > ray_tmax)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vector3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}

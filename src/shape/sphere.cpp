#include "sphere.hpp"

#include <algorithm>
#include <cmath>

#include "core/hitrecord.hpp"
#include "core/ray.hpp"
#include "maths/interval.hpp"
#include "maths/vector3.hpp"

sphere::sphere(const point3& center, float radius)
    : center(center), radius(std::max(1e-9f, radius)) {}

bool sphere::hit(const ray& r, interval ray_t, HitRecord& rec) const {
    vector3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0.0f)
        return false;
    auto sqrtd = std::sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (!ray_t.contains(root)) {
        root = (-half_b + sqrtd) / a;
        if (!ray_t.contains(root))
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vector3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}

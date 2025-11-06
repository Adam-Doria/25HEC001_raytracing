#include "sphere.hpp"

#include "core/hitrecord.hpp"

sphere::sphere(const point3& center, float radius, shared_ptr<material> material)
    : center(center), radius(std::max(1e-9f, radius)), mat(material) {
    auto rvector = vector3(radius, radius, radius);
    bbox = aabb(center - rvector, center + rvector);
}

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
    rec.mat = mat;

    return true;
}

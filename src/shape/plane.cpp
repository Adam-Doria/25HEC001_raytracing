#include "plane.hpp"

#include <cmath>

#include "core/hitrecord.hpp"
#include "core/ray.hpp"
#include "maths/interval.hpp"
#include "maths/vector3.hpp"

plane::plane(const point3& point_on_plane, const vector3& normal_vector,
             shared_ptr<material> material)
    : point(point_on_plane), mat(material) {
    auto length = normal_vector.length();
    if (length < 1e-6f) {
        normal = vector3(0.0f, 1.0f, 0.0f);
    } else {
        normal = normal_vector / length;
    }
}

bool plane::hit(const ray& r, interval ray_t, HitRecord& rec) const {
    float denom = dot(normal, r.direction());
    if (std::fabs(denom) < 1e-6f) {
        return false;
    }

    vector3 origin_to_point = point - r.origin();
    float t = dot(origin_to_point, normal) / denom;

    if (!ray_t.contains(t)) {
        return false;
    }

    rec.t = t;
    rec.p = r.at(t);
    rec.set_face_normal(r, normal);
    rec.mat = mat;

    return true;
}

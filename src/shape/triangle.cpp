#include "triangle.hpp"

#include <cmath>

#include "core/hitrecord.hpp"
#include "core/ray.hpp"
#include "maths/interval.hpp"
#include "maths/vector3.hpp"

triangle::triangle(const point3& v0, const point3& v1, const point3& v2,
                   shared_ptr<material> material)
    : v0(v0), v1(v1), v2(v2), mat(material) {
    // Calcul de la normale du triangle
    vector3 edge1 = v1 - v0;
    vector3 edge2 = v2 - v0;
    normal = unit_vector(cross(edge1, edge2));
}

bool triangle::hit(const ray& r, interval ray_t, HitRecord& rec) const {
    const float EPSILON = 1e-8f;
    vector3 edge1 = v1 - v0;
    vector3 edge2 = v2 - v0;

    vector3 h = cross(r.direction(), edge2);

    float a = dot(edge1, h);

    if (a > -EPSILON && a < EPSILON) {
        return false;  // Pas d'intersection
    }

    float f = 1.0f / a;
    vector3 s = r.origin() - v0;
    float u = f * dot(s, h);

    if (u < 0.0f || u > 1.0f) {
        return false;
    }

    vector3 q = cross(s, edge1);
    float v = f * dot(r.direction(), q);

    if (v < 0.0f || u + v > 1.0f) {
        return false;
    }

    float t = f * dot(edge2, q);

    if (!ray_t.contains(t)) {
        return false;
    }

    rec.t = t;
    rec.p = r.at(t);
    rec.set_face_normal(r, normal);
    rec.mat = mat;

    return true;
}

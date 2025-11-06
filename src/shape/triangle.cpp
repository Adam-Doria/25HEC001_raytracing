#include "triangle.hpp"

#include "core/hitrecord.hpp"

triangle::triangle(const point3& v0, const point3& v1, const point3& v2,
                   shared_ptr<material> material)
    : v0(v0), v1(v1), v2(v2), mat(material) {
    // Calcul de la normale du triangle
    vector3 edge1 = v1 - v0;
    vector3 edge2 = v2 - v0;
    normal = unit_vector(cross(edge1, edge2));

    // Calculer la bounding box du triangle
    point3 min_point(std::min({v0.x(), v1.x(), v2.x()}), std::min({v0.y(), v1.y(), v2.y()}),
                     std::min({v0.z(), v1.z(), v2.z()}));
    point3 max_point(std::max({v0.x(), v1.x(), v2.x()}), std::max({v0.y(), v1.y(), v2.y()}),
                     std::max({v0.z(), v1.z(), v2.z()}));

    // Ajouter un petit padding pour éviter les bounding boxes plates
    const float epsilon = 1e-4f;
    if (max_point.x() - min_point.x() < epsilon) {
        min_point = point3(min_point.x() - epsilon, min_point.y(), min_point.z());
        max_point = point3(max_point.x() + epsilon, max_point.y(), max_point.z());
    }
    if (max_point.y() - min_point.y() < epsilon) {
        min_point = point3(min_point.x(), min_point.y() - epsilon, min_point.z());
        max_point = point3(max_point.x(), max_point.y() + epsilon, max_point.z());
    }
    if (max_point.z() - min_point.z() < epsilon) {
        min_point = point3(min_point.x(), min_point.y(), min_point.z() - epsilon);
        max_point = point3(max_point.x(), max_point.y(), max_point.z() + epsilon);
    }

    bbox = aabb(min_point, max_point);
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

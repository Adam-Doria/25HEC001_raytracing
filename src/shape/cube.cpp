#include "cube.hpp"

#include "core/hitrecord.hpp"
#include "shape/triangle.hpp"

cube::cube(const point3& center, float size, shared_ptr<material> material)
    : center(center), size(size), mat(material) {
    float half_size = size / 2.0f;

    // Initialiser la bounding box
    auto half_vector = vector3(half_size, half_size, half_size);
    bbox = aabb(center - half_vector, center + half_vector);

    // Calcul des 8 sommets du cube
    point3 vertices[8];
    vertices[0] = center + vector3(-half_size, -half_size, -half_size);  // Arrière bas gauche
    vertices[1] = center + vector3(half_size, -half_size, -half_size);   // Arrière bas droit
    vertices[2] = center + vector3(half_size, half_size, -half_size);    // Arrière haut droit
    vertices[3] = center + vector3(-half_size, half_size, -half_size);   // Arrière haut gauche
    vertices[4] = center + vector3(-half_size, -half_size, half_size);   // Avant bas gauche
    vertices[5] = center + vector3(half_size, -half_size, half_size);    // Avant bas droit
    vertices[6] = center + vector3(half_size, half_size, half_size);     // Avant haut droit
    vertices[7] = center + vector3(-half_size, half_size, half_size);    // Avant haut gauche

    // Face arrière (z = -half_size)
    faces.add(make_shared<triangle>(vertices[0], vertices[1], vertices[2], mat));
    faces.add(make_shared<triangle>(vertices[0], vertices[2], vertices[3], mat));

    // Face avant (z = half_size)
    faces.add(make_shared<triangle>(vertices[4], vertices[6], vertices[5], mat));
    faces.add(make_shared<triangle>(vertices[4], vertices[7], vertices[6], mat));

    // Face gauche (x = -half_size)
    faces.add(make_shared<triangle>(vertices[0], vertices[3], vertices[7], mat));
    faces.add(make_shared<triangle>(vertices[0], vertices[7], vertices[4], mat));

    // Face droite (x = half_size)
    faces.add(make_shared<triangle>(vertices[1], vertices[5], vertices[6], mat));
    faces.add(make_shared<triangle>(vertices[1], vertices[6], vertices[2], mat));

    // Face bas (y = -half_size)
    faces.add(make_shared<triangle>(vertices[0], vertices[4], vertices[5], mat));
    faces.add(make_shared<triangle>(vertices[0], vertices[5], vertices[1], mat));

    // Face haut (y = half_size)
    faces.add(make_shared<triangle>(vertices[3], vertices[2], vertices[6], mat));
    faces.add(make_shared<triangle>(vertices[3], vertices[6], vertices[7], mat));
}

bool cube::hit(const ray& r, interval ray_t, HitRecord& rec) const {
    return faces.hit(r, ray_t, rec);
}

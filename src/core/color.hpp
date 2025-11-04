#pragma once

#include <cmath>

#include "maths/vector3.hpp"
#include "ray.hpp"

/**
 * @file color.hpp
 * @brief Fonctions utilitaires pour calculer les couleurs dans le raytracer.
 *
 * Ce fichier contient les fonctions pour déterminer la couleur d'un rayon
 * en fonction de sa direction et de l'environnement.
 */

/**
 * @brief Calcule la couleur d'un rayon avec un dégradé type espace (noir -> bleu marine)
 * @param r Le rayon pour lequel calculer la couleur
 * @return La couleur RGB correspondante
 *
 * Cette fonction crée un gradient vertical simulant l'espace , par espace je parle genre de système
 * solaire etc....:
 * - Noir profond en bas (quand le rayon pointe vers le bas)
 * - Bleu marine/indigo en haut (quand le rayon pointe vers le haut)
 */

inline float hit_sphere(const point3& center, float radius, const ray& r) {
    vector3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0f;  // Pas d'intersection
    } else {
        return (-b - std::sqrt(discriminant)) / (2.0 * a);
    }
}

inline color ray_color(const ray& r) {
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vector3 N = unit_vector(r.at(t) - vector3(0, 0, -1));
        return 0.5f * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vector3 unit_direction = unit_vector(r.direction());

    auto a = 0.5 * (unit_direction.y() + 1.0);

    color deep_space = color(0.02, 0.02, 0.05);
    color space_blue = color(0.1, 0.15, 0.35);
    return (1.0 - a) * deep_space + a * space_blue;
}

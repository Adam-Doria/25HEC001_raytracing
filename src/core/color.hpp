#pragma once

#include <memory>
#include <vector>

#include "hitrecord.hpp"
#include "hittable.hpp"
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
 * @brief Calcule la couleur de fond avec un dégradé type espace (noir -> bleu marine)
 * @param r Le rayon pour lequel calculer la couleur
 * @return La couleur RGB correspondante
 *
 * Cette fonction crée un gradient vertical simulant l'espace, par espace je parle genre de système
 * solaire etc....:
 * - Noir profond en bas (quand le rayon pointe vers le bas)
 * - Bleu marine/indigo en haut (quand le rayon pointe vers le haut)
 */
inline color background_color(const ray& r) {
    vector3 unit_direction = unit_vector(r.direction());
    auto t = 0.5f * (unit_direction.y() + 1.0f);
    color deep_space = color(0.02f, 0.02f, 0.05f);
    color space_blue = color(0.1f, 0.15f, 0.35f);
    return (1.0f - t) * deep_space + t * space_blue;
}

/**
 * @brief Calcule la couleur d'un rayon en tenant compte des objets de la scène
 * @param r Le rayon pour lequel calculer la couleur
 * @param world_objects Liste des objets hittables dans la scène
 * @return La couleur RGB correspondante
 *
 * Cette fonction détecte les intersections avec les objets de la scène.
 * Si le rayon touche un objet, retourne une couleur basée sur la normale.
 * Sinon, retourne la couleur de fond.
 */
inline color ray_color(const ray& r, const std::vector<std::shared_ptr<Hittable>>& world_objects) {
    HitRecord closest_hit;
    float nearest_distance = 1e9f;
    bool hit_found = false;

    for (const auto& object : world_objects) {
        HitRecord temp_hit;
        if (object->hit(r, 0.001f, nearest_distance, temp_hit)) {
            hit_found = true;
            nearest_distance = temp_hit.t;
            closest_hit = temp_hit;
        }
    }

    if (hit_found) {
        vector3 normal = closest_hit.normal;
        float intensity = (normal.y() + 1.0f) * 0.5f;
        return color(1.0f, intensity, 0.0f);
    }

    return background_color(r);
}

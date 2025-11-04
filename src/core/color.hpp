#pragma once

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
inline color ray_color(const ray& r) {
    vector3 unit_direction = unit_vector(r.direction());

    auto t = 0.5f * (unit_direction.y() + 1.0f);

    color deep_space = color(0.02f, 0.02f, 0.05f);
    color space_blue = color(0.1f, 0.15f, 0.35f);

    return (1.0f - t) * deep_space + t * space_blue;
}

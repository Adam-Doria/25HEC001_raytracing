#pragma once

/**
 * @file hitrecord.hpp
 * @brief Structure pour stocker les informations d'un impact rayon-objet.
 *
 * Contient les données renvoyées lorsqu'un rayon intersecte un objet : point
 * d'impact, normale, paramètre t, et indication face avant/arrière. Fournit
 * une méthode utilitaire pour orienter correctement la normale selon la
 * direction du rayon.
 */

#include <string>

#include "core/ray.hpp"
#include "maths/vector3.hpp"

/**
 * @brief Enregistrement d'un impact (hit) entre un rayon et un objet.
 *
 * Cette structure est remplie par les implémentations de `Hittable::hit` lorsqu'une
 * intersection valide est détectée. Elle contient les informations nécessaires
 * au shading (point d'impact, normale, paramètre t) et un indicateur indiquant
 * si l'impact se situe sur la face avant (par rapport au rayon entrant).
 */
class HitRecord {
public:
    point3 p;        /**< Point d'impact dans l'espace monde (x,y,z). */
    vector3 normal;  /**< Normale de la surface au point d'impact (orientée via set_face_normal). */
    double t;        /**< Paramètre t du rayon pour lequel r.at(t) == p. */
    bool front_face; /**< true si le rayon a frappé la face "avant" de la surface. */

    /**
     * @brief Calcule et fixe la normale orientée du HitRecord.
     *
     * La normale fournie (outward_normal) est supposée unitaire. Cette méthode
     * définit `front_face` en comparant la direction du rayon et la normale
     * sortante, puis stocke dans `normal` la normale orientée de manière à
     * toujours pointer contre le rayon entrant (utile pour le shading et la réfraction).
     *
     * @param r Le rayon incident.
     * @param outward_normal La normale sortante non orientée (unit vector).
     */
    void set_face_normal(const ray& r, const vector3& outward_normal);

    /**
     * @brief Affiche dans la console un message de debug concernant l'impact.
     *
     * Méthode utilitaire destinée au débogage : affiche le message fourni et
     * des informations succinctes sur l'impact (par exemple la distance t).
     *
     * @param message Message à afficher (par défaut : "Vous avez été touchée").
     */
    void log(const std::string& message = "Vous avez été touchée");
};

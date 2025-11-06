#pragma once

#include "lib/lib.hpp"

/**
 * @file sphere.hpp
 * @brief Déclaration de la classe `sphere`
 */

class ray;
class HitRecord;
class interval;

#include "core/hittable.hpp"
#include "material/material.hpp"

/**
 * @brief Représente une sphère géométrique dans la scène.
 *
 * La sphère est définie par son centre (point3) et son rayon (float).
 */
class sphere : public Hittable {
public:
    /**
     * @brief Construit une sphère.
     *
     * @param center Position du centre de la sphère dans l'espace monde.
     * @param radius Rayon de la sphère. Doit être strictement positif.
     *
     */
    sphere(const point3& center, float radius, shared_ptr<material> material);

    /**
     * @brief Teste l'intersection d'un rayon avec la sphère.
     *
     * @param r Le rayon testé (origine + direction).
     * @param ray_t L'intervalle acceptable pour t (min généralement > 0 pour éviter
     * l'auto-intersection, max utilisé pour trouver la racine la plus proche).
     * @param rec Référence vers la structure HitRecord à remplir en cas d'impact.
     * @return true si le rayon intersecte la sphère dans l'intervalle ray_t, false sinon.
     *
     */

    bool hit(const ray& r, interval ray_t, HitRecord& rec) const override;

    aabb bounding_box() const override {
        return bbox;
    }

private:
    point3 center;
    float radius;
    shared_ptr<material> mat;
    aabb bbox;
};

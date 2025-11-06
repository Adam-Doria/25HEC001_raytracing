#pragma once

#include "lib/lib.hpp"

/**
 * @file cube.hpp
 * @brief Déclaration de la classe `cube`
 */

class ray;
class HitRecord;
class interval;

#include "core/hittable.hpp"
#include "core/hittable_list.hpp"
#include "material/material.hpp"

/**
 * @brief Représente un cube géométrique dans la scène.
 *
 * Le cube est défini par son centre et sa taille. Il est composé de 12 triangles
 * (2 par face) pour former les 6 faces du cube.
 */
class cube : public Hittable {
public:
    /**
     * @brief Construit un cube.
     *
     * @param center Position du centre du cube dans l'espace monde.
     * @param size Taille du cube (longueur d'un côté). Doit être strictement positif.
     * @param material Matériau appliqué au cube.
     */
    cube(const point3& center, float size, shared_ptr<material> material);

    /**
     * @brief Teste l'intersection d'un rayon avec le cube.
     *
     * @param r Le rayon testé (origine + direction).
     * @param ray_t L'intervalle acceptable pour t.
     * @param rec Référence vers la structure HitRecord à remplir en cas d'impact.
     * @return true si le rayon intersecte le cube dans l'intervalle ray_t, false sinon.
     */
    bool hit(const ray& r, interval ray_t, HitRecord& rec) const override;

    aabb bounding_box() const override {
        return bbox;
    }

private:
    point3 center;
    float size;
    shared_ptr<material> mat;
    hittable_list faces;  // Liste des triangles formant le cube
    aabb bbox;
};

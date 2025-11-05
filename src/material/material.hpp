#pragma once

#include "core/hittable.hpp"
#include "core/ray.hpp"
#include "maths/vector3.hpp"

class HitRecord;

/**
 * @file material.hpp
 * @brief Classe de base pour les matériaux dans le raytracer.
 *
 * Cette classe définit l'interface pour tous les matériaux qui peuvent
 * interagir avec les rayons lumineux (réflexion, réfraction, absorption, etc.).
 */

/**
 * @class material
 * @brief Classe de base abstraite pour les matériaux.
 *
 */

class material {
public:
    virtual ~material() = default;

    /**
     * @brief Calcule la diffusion d'un rayon sur le matériau.
     *
     * @param r_in Le rayon entrant
     * @param rec Les informations sur le point d'intersection
     * @param attenuation La couleur d'atténuation du rayon diffusé
     * @param scattered Le rayon sortant
     * @return true si le rayon est diffusé, false s'il est absorbé
     */
    virtual bool scatter(const ray& r_in, const HitRecord& rec, color& attenuation,
                         ray& scattered) const {
        return false;
    }
};

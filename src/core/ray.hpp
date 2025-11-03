#pragma once

#include "maths/vector3.hpp"

/**
 * @file ray.hpp
 * @brief Représente un rayon, qui contient une origine et une direction.
 *
 * Ce fichier contient la classe `ray` qui encapsule un point d'origine
 * et une direction. La classe fournit des accesseurs et une méthode
 * utilitaire pour évaluer la position le long du rayon.
 */

/**
 * @class ray
 * @brief Un rayon défini par une origine et une direction.
 *
 * Le rayon est représenté paramétriquement : P(t) = origine + t * direction.
 */
class ray {
public:
    ray() {}

    /**
     * @brief Constructeur principal.
     * @param origin Point d'origine du rayon.
     * @param direction Vecteur directionnel du rayon.
     */
    ray(const point3& origin, const vector3& direction) : orig(origin), dir(direction) {}

    /**
     * @brief Récupère l'origine du rayon.
     * @return Référence en lecture seule sur le point origine.
     */
    const point3& origin() const {
        return orig;
    }

    /**
     * @brief Récupère la direction du rayon.
     * @return Référence en lecture sur le vecteur direction.
     */
    const vector3& direction() const {
        return dir;
    }

    /**
     * @brief Calcule la position le long du rayon pour un paramètre t.
     * @param t Paramètre scalaire (distance le long de la direction).
     * @return Le point P(t) = origine + t * direction.
     */
    point3 at(float t) const {
        return orig + t * dir;
    }

private:
    /**
     * @brief Origine du rayon.
     */
    point3 orig;

    /**
     * @brief Direction du rayon.
     */
    vector3 dir;
};

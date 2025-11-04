#pragma once

/**
 * @file hittable.hpp
 * @brief Interface abstraite pour les objets géométriques testables par rayon.
 *
 * Ce fichier contient la définition de la classe abstraite `Hittable`. Les
 * objets dérivés (sphères, plans, triangles, etc.) doivent implémenter la méthode
 * `hit` qui teste l'intersection avec un rayon et remplit un HitRecord.
 */

class ray;
struct HitRecord;

/**
 * @brief Interface pour un objet qui peut être frappé par un rayon (ray-hittable).
 *
 * `Hittable` définit l'API minimale requise par le traceur de rayons :
 * un destructeur virtuel et une méthode pure virtuelle `hit`. Les implémentations
 * doivent respecter la sémantique de `hit` décrite ci-dessous.
 */
class Hittable {
public:
    /**
     * @brief Destructeur virtuel par défaut.
     *
     * Déclaré `noexcept` et `= default` car la classe n'a pas de ressources à
     * libérer elle-même. Nécessaire pour une destruction correcte via un pointeur
     * vers la base.
     */
    virtual ~Hittable() noexcept = default;

    /**
     * @brief Teste si un rayon intersecte l'objet.
     *
     * Si une intersection valide (réelle) est trouvée entre `ray_tmin` et `ray_tmax`,
     * la méthode doit remplir `rec` (HitRecord) avec les informations relatives
     * à l'impact (point, normale, t, matériau, etc.) et retourner `true`.
     *
     * @param r Le rayon testé (origine + direction).
     * @param ray_tmin Borne inférieure acceptable pour le paramètre t du rayon
     *                 (souvent une petite valeur > 0 pour éviter l'auto-intersection).
     * @param ray_tmax Borne supérieure acceptable pour t (sert à garder la plus
     *                 proche intersection).
     * @param rec Référence vers la structure HitRecord à remplir si l'impact est valide.
     * @return `true` si le rayon intersecte l'objet dans [ray_tmin, ray_tmax], `false` sinon.
     */
    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const = 0;
};

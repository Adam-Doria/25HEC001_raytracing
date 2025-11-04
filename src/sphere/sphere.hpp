#pragma once

/**
 * @file sphere.hpp
 * @brief Déclaration de la classe `sphere` (objet hittable : intersection rayon-sphère).
 *
 * Contient la définition de la classe sphere qui dérive de Hittable et implémente
 * le test d'intersection rayon-sphère. Le type `point3` est un alias vers `vector3`
 * (défini dans `maths/vector3.hpp`).
 */

class ray;
class HitRecord;

#include "hittable/hittable.hpp"
#include "maths/vector3.hpp"

/**
 * @brief Représente une sphère géométrique dans la scène.
 *
 * La sphère est définie par son centre (point3) et son rayon (double).
 * Elle implémente la méthode `hit(...)` héritée de `Hittable` pour tester
 * l'intersection avec un rayon.
 */
class sphere : public Hittable {
public:
    /**
     * @brief Construit une sphère.
     *
     * @param center Position du centre de la sphère dans l'espace monde.
     * @param radius Rayon de la sphère. Doit être strictement positif.
     *
     * @note Le constructeur n'effectue pas de normalisation particulière du rayon ;
     *       appeler avec radius <= 0 peut provoquer un comportement indéfini lors
     *       des calculs (division par radius). Il est recommandé de fournir un rayon > 0.
     */
    sphere(const point3& center, double radius);

    /**
     * @brief Teste l'intersection d'un rayon avec la sphère.
     *
     * Cette méthode implémente le contrat défini par `Hittable::hit`.
     * Elle résout la quadratique pour trouver les racines t, et retourne la
     * première racine valide située dans l'intervalle [ray_tmin, ray_tmax].
     *
     * Si une intersection valide est trouvée, le @p rec (HitRecord) est rempli
     * avec :
     *  - rec.t : la valeur paramétrique t du rayon pour l'intersection
     *  - rec.p : le point d'intersection (r.at(rec.t))
     *  - rec.normal : la normale de surface à ce point (orientée avec set_face_normal)
     *
     * @param r Le rayon testé (origine + direction).
     * @param ray_tmin La borne minimale acceptable pour t (généralement > 0 pour éviter
     * l'auto-intersection).
     * @param ray_tmax La borne maximale acceptable pour t (utilisée pour trouver la racine la plus
     * proche).
     * @param rec Référence vers la structure HitRecord à remplir en cas d'impact.
     * @return true si le rayon intersecte la sphère dans l'intervalle [ray_tmin, ray_tmax], false
     * sinon.
     *
     * @see Hittable::hit
     */
    bool hit(const ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const override;

private:
    point3 center; /**< Centre de la sphère (point3 / vector3) */
    double radius; /**< Rayon de la sphère (unités du monde) */
};

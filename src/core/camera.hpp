#pragma once

#include "core/hitrecord.hpp"
#include "core/hittable.hpp"
#include "core/hittable_list.hpp"
#include "core/ray.hpp"
#include "image/image.hpp"
#include "maths/interval.hpp"
#include "maths/vector3.hpp"

/**
 * @brief Classe représentant la caméra du raytracer
 *
 * Cette classe gère la configuration de la caméra, le rendu de la scène
 * et le calcul des couleurs des rayons.
 */
class camera {
public:
    // Configuration de la caméra
    float aspect_ratio = 16.0f / 9.0f;
    int image_width = 1080;
    point3 camera_origin = point3(0, 0, 0);
    float focal_length = 1.0f;
    float vfov = 90.0f;
    int samples_per_pixel = 10;

    /**
     * @brief Rend la scène complète
     * @param world La liste des objets hittables dans la scène
     * @param output_filename Le nom du fichier de sortie
     */
    void render(const hittable_list& world, const std::string& output_filename = "scene.png");

private:
    // Paramètres calculés
    int image_height;
    float viewport_width;
    vector3 horizontal;
    vector3 vertical;
    vector3 pixel_step_u;
    vector3 pixel_step_v;
    vector3 viewport_top_left;
    vector3 first_pixel_center;
    float pixel_samples_scale;

    /**
     * @brief Initialise les paramètres de la caméra
     */
    void initialize_camera();

    /**
     * @brief Calcule la couleur de fond avec un dégradé type espace
     * @param r Le rayon pour lequel calculer la couleur
     * @return La couleur RGB correspondante
     */
    color background_color(const ray& r) const;

    /**
     * @brief Calcule la couleur d'un rayon en tenant compte des objets de la scène
     * @param r Le rayon pour lequel calculer la couleur
     * @param world La liste des objets hittables dans la scène
     * @return La couleur RGB correspondante
     */
    color ray_color(const ray& r, const hittable_list& world) const;

    /**
     * @brief Génère un rayon pour un pixel donné avec un offset aléatoire
     * @param i Coordonnée x du pixel
     * @param j Coordonnée y du pixel
     * @return Un rayon partant de la caméra vers un point aléatoire autour du centre du pixel
     */
    ray get_ray(int i, int j) const;

    /**
     * @brief Génère un vecteur aléatoire dans le carré unitaire [-0.5, 0.5]
     * @return Un vecteur 3D avec composantes x,y aléatoires et z=0
     */
    vector3 sample_square() const;
};
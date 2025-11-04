#pragma once

#include <iostream>
#include <vector>

#include "maths/vector3.hpp"

/**
 * @file image.hpp
 * @brief Classe pour créer et manipuler des images en mémoire.
 *
 * Cette classe encapsule un buffer de pixels (couleurs) et fournit
 * des méthodes pour définir/récupérer des pixels et sauvegarder l'image
 * au format PNG via lodepng.
 */

/**
 * @class Image
 * @brief Représente une image 2D avec un buffer de couleurs.
 *
 * L'image stocke ses pixels dans un buffer 1D (row-major order).
 * Permet de créer, manipuler et exporter des images PNG.
 */

class Image {
private:
    unsigned int width = 0;
    unsigned int height = 0;
    std::vector<color> buffer;

public:
    Image(unsigned int w, unsigned int h);

    Image(unsigned int w, unsigned int h, color c);

    ~Image();

    void SetPixel(unsigned int x, unsigned int y, color pixel_color);

    color GetPixel(unsigned int x, unsigned int y);

    /**
     * @brief Sauvegarde l'image au format PNG.
     * @param filename Chemin du fichier de sortie (ex: "output.png")
     *
     * Utilise lodepng pour encoder l'image. Les couleurs sont converties
     * de float [0.0, 1.0] vers unsigned char [0, 255].
     */
    void WriteFile(const char* filename);
};

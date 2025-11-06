#pragma once

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

#include "core/hittable_list.hpp"
#include "lib/lib.hpp"
#include "material/material.hpp"
#include "shape/triangle.hpp"

class read_mesh {
public:
    /**
     * @brief Constructeur du lecteur de mesh
     *
     * @param filepath Chemin vers le fichier .obj
     * @param world Pointeur vers la liste des objets de la scène
     * @param m Matériau à appliquer au mesh
     * @param scale Facteur d'échelle à appliquer au mesh
     * @param origin Position de base du mesh dans la scène
     */
    read_mesh(const std::string& filepath, hittable_list* world, shared_ptr<material> m,
              float scale, const point3& origin)
        : path(filepath), scene(world), mat_ptr(m), scale_factor(scale), base(origin) {}

    void add_mesh() {
        FILE* file = fopen(path.c_str(), "r");
        if (file == NULL) {
            std::cerr << "Erreur: Impossible d'ouvrir le fichier " << path << std::endl;
            return;
        }

        std::vector<point3> mesh_vertices;
        std::vector<std::vector<int>> mesh_faces;

        char lineHeader[128];
        int result;
        std::vector<float> temp_vertex(3);
        std::vector<int> temp_face(3);
        int temp_index;

        while (true) {
            result = fscanf(file, "%s", lineHeader);
            if (result == EOF) {
                break;
            }

            if (strcmp(lineHeader, "v") == 0) {
                int matches =
                    fscanf(file, "%f %f %f\n", &temp_vertex[0], &temp_vertex[1], &temp_vertex[2]);
                if (matches == 3) {
                    mesh_vertices.push_back(point3(temp_vertex[0], temp_vertex[1], temp_vertex[2]));
                }
            } else if (strcmp(lineHeader, "f") == 0) {
                // TODO : ajouter la texture et les normales (vt/vn)
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d", &temp_face[0], &temp_index,
                                     &temp_index, &temp_face[1], &temp_index, &temp_index,
                                     &temp_face[2], &temp_index, &temp_index);

                mesh_faces.push_back(temp_face);
            }
        }

        fclose(file);

        for (size_t i = 0; i < mesh_vertices.size(); i++) {
            mesh_vertices[i] = mesh_vertices[i] * scale_factor + base;
        }

        for (size_t j = 0; j < mesh_faces.size(); j++) {
            // obj commence à 1 donc on soustrait 1
            int idx0 = mesh_faces[j][0] - 1;
            int idx1 = mesh_faces[j][1] - 1;
            int idx2 = mesh_faces[j][2] - 1;

            if (idx0 >= 0 && idx0 < mesh_vertices.size() && idx1 >= 0 &&
                idx1 < mesh_vertices.size() && idx2 >= 0 && idx2 < mesh_vertices.size()) {
                scene->add(make_shared<triangle>(mesh_vertices[idx0], mesh_vertices[idx1],
                                                 mesh_vertices[idx2], mat_ptr));
            }
        }
        return;
    }

private:
    std::string path;
    hittable_list* scene;
    shared_ptr<material> mat_ptr;
    float scale_factor;
    point3 base;
};

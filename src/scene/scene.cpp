#include "scene.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "core/hitrecord.hpp"
#include "core/hittable_list.hpp"
#include "material/material.hpp"
#include "shape/cube.hpp"
#include "shape/plane.hpp"
#include "shape/read_mesh.hpp"
#include "shape/sphere.hpp"
#include "shape/triangle.hpp"

using json = nlohmann::json;

void load_scene_from_json_file(const std::string& filename, hittable_list& world) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open scene file: " << filename << std::endl;
        return;
    }

    json j;
    file >> j;

    for (auto& obj : j["objects"]) {
        std::shared_ptr<material> mat = nullptr;

        // Create material
        if (obj.contains("material")) {
            auto m = obj["material"];
            std::string type = m["type"];
            if (type == "lambertian") {
                mat = std::make_shared<lambertian>(
                    color(m["albedo"][0], m["albedo"][1], m["albedo"][2]));
            } else if (type == "metal") {
                mat =
                    std::make_shared<metal>(color(m["albedo"][0], m["albedo"][1], m["albedo"][2]));
            } else {
                std::cerr << "Unknown material type: " << type << std::endl;
            }
        }

        // Create object
        std::string type = obj["type"];
        if (type == "sphere") {
            auto center = point3(obj["center"][0], obj["center"][1], obj["center"][2]);
            double radius = obj["radius"];
            world.add(std::make_shared<sphere>(center, radius, mat));
        } else if (type == "cube") {
            auto center = point3(obj["center"][0], obj["center"][1], obj["center"][2]);
            double size = obj["size"];
            world.add(std::make_shared<cube>(center, size, mat));
        } else if (type == "plane") {
            auto point = point3(obj["point"][0], obj["point"][1], obj["point"][2]);
            auto normal = vector3(obj["normal"][0], obj["normal"][1], obj["normal"][2]);
            world.add(std::make_shared<plane>(point, normal, mat));
        } else if (type == "triangle") {
            auto v0 = point3(obj["v0"][0], obj["v0"][1], obj["v0"][2]);
            auto v1 = point3(obj["v1"][0], obj["v1"][1], obj["v1"][2]);
            auto v2 = point3(obj["v2"][0], obj["v2"][1], obj["v2"][2]);
            world.add(std::make_shared<triangle>(v0, v1, v2, mat));
        } else if (type == "mesh") {
            std::string filepath = obj["file"];
            float scale = obj.value("scale", 1.0f);
            auto origin = obj.contains("origin")
                              ? point3(obj["origin"][0], obj["origin"][1], obj["origin"][2])
                              : point3(0, 0, 0);
            read_mesh mesh_loader(filepath, &world, mat, scale, origin);
            mesh_loader.add_mesh();
        } else {
            std::cerr << "Unknown object type: " << type << std::endl;
        }
    }
}

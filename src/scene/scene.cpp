#include "scene.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "core/hitrecord.hpp"
#include "material/material.hpp"
#include "shape/box.hpp"
#include "shape/plane.hpp"
#include "shape/sphere.hpp"

using json = nlohmann::json;

std::vector<std::shared_ptr<Hittable>> load_scene_from_json_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open scene file: " << filename << std::endl;
        return {};
    }

    json j;
    file >> j;

    std::vector<std::shared_ptr<Hittable>> world;

    for (auto& obj : j["objects"]) {
        std::shared_ptr<material> mat = nullptr;

        // Create material
        if (obj.contains("material")) {
            auto m = obj["material"];
            std::string type = m["type"];
            if (type == "lambertian") {
                mat = std::make_shared<Lambertian>(
                    color(m["albedo"][0], m["albedo"][1], m["albedo"][2]));
            } else if (type == "metal") {
                mat = std::make_shared<Metal>(color(m["albedo"][0], m["albedo"][1], m["albedo"][2]),
                                              m.value("fuzz", 0.0));
            } else if (type == "dielectric") {
                mat = std::make_shared<Dielectric>(m["ir"]);
            } else {
                std::cerr << "Unknown material type: " << type << std::endl;
            }
        }

        // Create object
        std::string type = obj["type"];
        if (type == "sphere") {
            auto center = point3(obj["center"][0], obj["center"][1], obj["center"][2]);
            double radius = obj["radius"];
            world.push_back(std::make_shared<sphere>(center, radius, mat));
        } else if (type == "box") {
            auto min_pt = point3(obj["min"][0], obj["min"][1], obj["min"][2]);
            auto max_pt = point3(obj["max"][0], obj["max"][1], obj["max"][2]);
            world.push_back(std::make_shared<Box>(min_pt, max_pt, mat));
        } else if (type == "plane") {
            auto point = point3(obj["point"][0], obj["point"][1], obj["point"][2]);
            auto normal = vector3(obj["normal"][0], obj["normal"][1], obj["normal"][2]);
            world.push_back(std::make_shared<Plane>(point, normal, mat));
        } else {
            std::cerr << "Unknown object type: " << type << std::endl;
        }
    }

    return world;
}

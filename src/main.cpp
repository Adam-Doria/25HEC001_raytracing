#include <vector>

#include "core/bvh_node.hpp"
#include "core/camera.hpp"
#include "core/hitrecord.hpp"
#include "core/hittable_list.hpp"
#include "core/ray.hpp"
#include "image/image.hpp"
#include "lib/chrono_timer.hpp"
#include "material/material.hpp"
#include "shape/cube.hpp"
#include "shape/plane.hpp"
#include "shape/read_mesh.hpp"
#include "shape/sphere.hpp"
#include "shape/triangle.hpp"

int main(int argc, char* argv[]) {
    bool use_bvh = true;
    bool use_multithreading = true;

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--no-bvh") {
            use_bvh = false;
        } else if (std::string(argv[i]) == "--no-mt") {
            use_multithreading = false;
        }
    }

    // Camera setup
    camera cam;
    cam.aspect_ratio = 16.0f / 9.0f;
    cam.image_width = 1920;
    cam.camera_origin = point3(0, 0, 0);
    cam.vfov = 45.0f;
    cam.focal_length = 1.0f;
    cam.samples_per_pixel = 500;
    cam.max_depth = 5;

    // World
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.2, 0.1));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8));
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2));
    auto material_cube = make_shared<lambertian>(color(0.2, 0.8, 0.3));
    auto material_dino = make_shared<metal>(color(0.4, 0.7, 0.3));
    auto material_spaceship = make_shared<lambertian>(color(0.7, 0.7, 0.7));

    world.add(make_shared<sphere>(point3(0, 0, -5), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0, -5.5), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0, -5.5), 0.5, material_right));
    world.add(
        make_shared<plane>(point3(0.0f, -0.5f, 0.0f), vector3(0.0f, 1.0f, 0.0f), material_ground));
    world.add(std::make_shared<triangle>(point3(-0.8, -0.5, -0.5), point3(-0.2, -0.5, -0.5),
                                         point3(-0.5, 0.3, -0.5), material_left));

    world.add(std::make_shared<triangle>(point3(0.2, 0.3, -0.8), point3(0.8, 0.3, -0.8),
                                         point3(0.5, -0.5, -0.8), material_center));

    world.add(make_shared<cube>(point3(0, 1.2, -4), 0.8, material_cube));

    // read_mesh dino_loader("dino.obj", &world, material_dino, 0.1f, point3(-2, -0.5, -6));
    // dino_loader.add_mesh();

    if (use_bvh) {
        world = hittable_list(make_shared<bvh_node>(world));
    }

    // Render
    std::string output_filename = "scene_with_mesh.png";
    if (!use_bvh)
        output_filename = "scene_no_bvh.png";
    if (!use_multithreading)
        output_filename = "scene_no_mt.png";
    if (!use_bvh && !use_multithreading)
        output_filename = "scene_baseline.png";

    cam.render(world, output_filename, use_multithreading);

    return 0;
}

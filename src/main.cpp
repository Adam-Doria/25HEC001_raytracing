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
        std::string arg = argv[i];
        if (arg == "--no-bvh") {
            use_bvh = false;
        } else if (arg == "--no-mt") {
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

    // Add 500 spheres in deterministic clusters for natural distribution
    int sphere_count = 0;

    // Cluster 1: Dense cluster on the left (-4 to -2, z: -8 to -5) - 150 spheres (mix)
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 10; j++) {
            point3 center(-4 + i * 0.15, -0.4 + (i % 3) * 0.2, -8 + j * 0.3);
            color albedo(0.3 + i * 0.03, 0.2 + j * 0.05, 0.6);
            auto mat = (i + j) % 3 == 0 ? (shared_ptr<material>)make_shared<metal>(albedo)
                                        : (shared_ptr<material>)make_shared<lambertian>(albedo);
            world.add(make_shared<sphere>(center, 0.08, mat));
            sphere_count++;
        }
    }

    // Cluster 2: Medium cluster on the right (1 to 3.5, z: -9 to -6) - 120 spheres (mostly metal)
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            point3 center(1 + i * 0.22, -0.3 + (j % 2) * 0.15, -9 + j * 0.3);
            color albedo(0.7, 0.5 + i * 0.02, 0.4 + j * 0.03);
            auto mat = j % 3 == 0 ? (shared_ptr<material>)make_shared<lambertian>(albedo)
                                  : (shared_ptr<material>)make_shared<metal>(albedo);
            world.add(make_shared<sphere>(center, 0.09, mat));
            sphere_count++;
        }
    }

    // Cluster 3: Sparse cluster in center (-1 to 1, z: -6 to -4) - 80 spheres (alternating)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 8; j++) {
            point3 center(-1 + i * 0.2, -0.2 + (i + j) % 3 * 0.1, -6 + j * 0.25);
            color albedo(0.5 + i * 0.03, 0.6, 0.3 + j * 0.04);
            auto mat = (i + j) % 2 == 0 ? (shared_ptr<material>)make_shared<lambertian>(albedo)
                                        : (shared_ptr<material>)make_shared<metal>(albedo);
            world.add(make_shared<sphere>(center, 0.07, mat));
            sphere_count++;
        }
    }

    // Cluster 4: Small dense cluster top-left (-3 to -1.5, z: -4 to -3) - 60 spheres (mix)
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 5; j++) {
            point3 center(-3 + i * 0.13, 0.5 + j * 0.15, -4 + j * 0.2);
            color albedo(0.8, 0.3 + i * 0.04, 0.5);
            auto mat = i % 2 == 0 ? (shared_ptr<material>)make_shared<metal>(albedo)
                                  : (shared_ptr<material>)make_shared<lambertian>(albedo);
            world.add(make_shared<sphere>(center, 0.06, mat));
            sphere_count++;
        }
    }

    // Cluster 5: Vertical spread (x: 0.5, y: -0.4 to 1.5, z: -7) - 50 spheres (mostly lambertian)
    for (int i = 0; i < 50; i++) {
        point3 center(0.5 + (i % 5) * 0.1, -0.4 + i * 0.04, -7 + (i % 7) * 0.15);
        color albedo(0.4, 0.7, 0.6 + i * 0.006);
        auto mat = i % 4 == 0 ? (shared_ptr<material>)make_shared<metal>(albedo)
                              : (shared_ptr<material>)make_shared<lambertian>(albedo);
        world.add(make_shared<sphere>(center, 0.05, mat));
        sphere_count++;
    }

    // Cluster 6: Far background scattered (z: -12 to -10) - 40 spheres (mix)
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 5; j++) {
            point3 center(-4 + i * 1.0, 0.3 + j * 0.2, -12 + i * 0.25);
            color albedo(0.2 + i * 0.08, 0.4, 0.8);
            auto mat = (i % 2 == 0) ? (shared_ptr<material>)make_shared<lambertian>(albedo)
                                    : (shared_ptr<material>)make_shared<metal>(albedo);
            world.add(make_shared<sphere>(center, 0.12, mat));
            sphere_count++;
        }
    }

    // Fill remaining spheres with a loose grid pattern to reach 500 (alternating materials)
    while (sphere_count < 500) {
        int idx = sphere_count - 470;
        int row = idx / 10;
        int col = idx % 10;
        point3 center(-3 + col * 0.6, 1.0 + row * 0.15, -8 + row * 0.4);
        color albedo(0.6, 0.5 + col * 0.03, 0.7);
        auto mat = (col + row) % 2 == 0 ? (shared_ptr<material>)make_shared<lambertian>(albedo)
                                        : (shared_ptr<material>)make_shared<metal>(albedo);
        world.add(make_shared<sphere>(center, 0.07, mat));
        sphere_count++;
    }

    if (use_bvh) {
        world = hittable_list(make_shared<bvh_node>(world));
    }

    // Render
    std::string output_filename = "scene_with_100_spheres.png";
    if (!use_bvh)
        output_filename = "scene_no_bvh.png";
    if (!use_multithreading)
        output_filename = "scene_no_mt.png";
    if (!use_bvh && !use_multithreading)
        output_filename = "scene_baseline.png";

    cam.render(world, output_filename, use_multithreading);

    return 0;
}

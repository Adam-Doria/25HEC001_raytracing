#include <vector>

#include "core/camera.hpp"
#include "core/hitrecord.hpp"
#include "core/hittable_list.hpp"
#include "core/ray.hpp"
#include "image/image.hpp"
#include "lib/chrono_timer.hpp"
#include "shape/plane.hpp"
#include "shape/sphere.hpp"
#include "shape/triangle.hpp"

int main() {
    // Camera setup
    camera cam;
    cam.aspect_ratio = 16.0f / 9.0f;
    cam.image_width = 1920;
    cam.camera_origin = point3(0, 0, 0);
    cam.vfov = 45.0f;
    cam.focal_length = 1.0f;
    cam.max_depth = 5;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -5), 0.5));
    world.add(make_shared<sphere>(point3(-1.0, 0, -5.5), 0.5));
    world.add(make_shared<sphere>(point3(1.0, 0, -5.5), 0.5));
    world.add(make_shared<plane>(point3(0.0f, -0.5f, 0.0f), vector3(0.0f, 1.0f, 0.0f)));
    world.add(std::make_shared<triangle>(point3(-0.8, -0.5, -0.5), point3(-0.2, -0.5, -0.5),
                                         point3(-0.5, 0.3, -0.5)));

    world.add(std::make_shared<triangle>(point3(0.2, 0.3, -0.8), point3(0.8, 0.3, -0.8),
                                         point3(0.5, -0.5, -0.8)));

    // Render
    cam.render(world, "scene.png");

    return 0;
}

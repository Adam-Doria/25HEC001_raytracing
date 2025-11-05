#include <vector>

#include "core/camera.hpp"
#include "core/hitrecord.hpp"
#include "core/hittable_list.hpp"
#include "core/ray.hpp"
#include "image/image.hpp"
#include "lib/chrono_timer.hpp"
#include "shape/sphere.hpp"

int main() {
    // Camera setup
    camera cam;
    cam.aspect_ratio = 16.0f / 9.0f;
    cam.image_width = 1080;
    cam.camera_origin = point3(0, 0, 0);
    cam.viewport_height = 2.0f;
    cam.focal_length = 1.0f;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(-1.0, 0, -1.5), 0.5));
    world.add(make_shared<sphere>(point3(1.0, 0, -1.5), 0.5));

    // Render
    cam.render(world, "scene.png");

    return 0;
}

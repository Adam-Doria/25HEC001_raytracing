#include <iostream>
#include <memory>
#include <vector>

#include "core/color.hpp"
#include "core/hitrecord.hpp"
#include "core/ray.hpp"
#include "image/image.hpp"
#include "maths/vector3.hpp"
#include "shape/sphere.hpp"
#include "timer/chrono_timer.hpp"

color ray_color(const ray& ray, const std::vector<std::shared_ptr<Hittable>>& world_objects) {
    HitRecord closest_hit;
    double nearest_distance = 1e9;
    bool hit_found = false;

    for (const auto& object : world_objects) {
        HitRecord temp_hit;
        if (object->hit(ray, 0.001, nearest_distance, temp_hit)) {
            hit_found = true;
            nearest_distance = temp_hit.t;
            closest_hit = temp_hit;
        }
    }

    if (hit_found) {
        vector3 normal = closest_hit.normal;
        return 0.5 * color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    }

    vector3 unit_dir = unit_vector(ray.direction());
    double t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
    std::cout << "Starting Rayborn renderer...\n";

    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    int image_height = static_cast<int>(image_width / aspect_ratio);

    Image canvas(image_width, image_height);

    point3 camera_origin(0, 0, 0);
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    vector3 horizontal(viewport_width, 0, 0);
    vector3 vertical(0, viewport_height, 0);

    vector3 pixel_step_u = horizontal / static_cast<double>(image_width);
    vector3 pixel_step_v = vertical / static_cast<double>(image_height);

    vector3 viewport_top_left =
        camera_origin - vector3(viewport_width / 2, viewport_height / 2, focal_length);
    vector3 first_pixel_center = viewport_top_left + 0.5 * (pixel_step_u + pixel_step_v);

    std::vector<std::shared_ptr<Hittable>> world;
    world.push_back(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.push_back(std::make_shared<sphere>(point3(-1.0, 0, -1.5), 0.5));
    world.push_back(std::make_shared<sphere>(point3(1.0, 0, -1.5), 0.5));
    world.push_back(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

    Chrono render_timer;
    render_timer.start();

    for (int y = 0; y < image_height; ++y) {
        for (int x = 0; x < image_width; ++x) {
            vector3 pixel_pos =
                first_pixel_center + float(x) * pixel_step_u + float(y) * pixel_step_v;
            ray ray_to_pixel(camera_origin, pixel_pos - camera_origin);

            color pixel_color = ray_color(ray_to_pixel, world);
            canvas.SetPixel(x, image_height - 1 - y, pixel_color);
        }
    }

    canvas.WriteFile("plan.png");
    render_timer.log("Rendering finished");

    std::cout << "Rayborn rendering complete!\n";
    return 0;
}

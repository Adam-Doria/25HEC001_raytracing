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

int main() {
    std::cout << "Starting Rayborn renderer...\n";

    const float aspect_ratio = 16.0 / 9.0;
    const int image_width = 1080;
    int image_height = static_cast<int>(image_width / aspect_ratio);

    Image canvas(image_width, image_height);

    point3 camera_origin(0, 0, 0);
    float viewport_height = 2.0;
    float viewport_width = aspect_ratio * viewport_height;
    float focal_length = 1.0;

    vector3 horizontal(viewport_width, 0, 0);
    vector3 vertical(0, viewport_height, 0);

    vector3 pixel_step_u = horizontal / static_cast<float>(image_width);
    vector3 pixel_step_v = vertical / static_cast<float>(image_height);

    vector3 viewport_top_left =
        camera_origin - vector3(viewport_width / 2, viewport_height / 2, focal_length);
    vector3 first_pixel_center = viewport_top_left + 0.5 * (pixel_step_u + pixel_step_v);

    std::vector<std::shared_ptr<Hittable>> world;
    world.push_back(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.push_back(std::make_shared<sphere>(point3(-1.0, 0, -1.5), 0.5));
    world.push_back(std::make_shared<sphere>(point3(1.0, 0, -1.5), 0.5));

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

    canvas.WriteFile("scene.png");
    render_timer.log("Rendering finished");

    std::cout << "Rayborn rendering complete!\n";
    return 0;
}

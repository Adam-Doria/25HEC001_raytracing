#include "camera.hpp"

#include <iostream>

#include "lib/chrono_timer.hpp"

void camera::render(const hittable_list& world, const std::string& output_filename) {
    initialize_camera();

    Image canvas(image_width, image_height);

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

    canvas.WriteFile(output_filename.c_str());
    render_timer.log("Rendering finished");
}

void camera::initialize_camera() {
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    float image_ratio = image_width / static_cast<float>(image_height);
    viewport_width = image_ratio * viewport_height;

    horizontal = vector3(viewport_width, 0, 0);
    vertical = vector3(0, viewport_height, 0);

    pixel_step_u = horizontal / static_cast<float>(image_width);
    pixel_step_v = vertical / static_cast<float>(image_height);

    viewport_top_left =
        camera_origin - vector3(viewport_width / 2, viewport_height / 2, focal_length);
    first_pixel_center = viewport_top_left + 0.5 * (pixel_step_u + pixel_step_v);
}

color camera::background_color(const ray& r) const {
    vector3 unit_direction = unit_vector(r.direction());
    auto t = 0.5f * (unit_direction.y() + 1.0f);
    color deep_space = color(0.02f, 0.02f, 0.05f);
    color space_blue = color(0.1f, 0.15f, 0.35f);
    return (1.0f - t) * deep_space + t * space_blue;
}

color camera::ray_color(const ray& r, const hittable_list& world) const {
    HitRecord rec;
    interval ray_t(0.001f, 1e9f);

    if (world.hit(r, ray_t, rec)) {
        vector3 normal = rec.normal;
        float intensity = (normal.y() + 1.0f) * 0.5f;
        return color(1.0f, intensity, 0.0f);
    }

    return background_color(r);
}

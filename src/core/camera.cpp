#include "camera.hpp"

#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

#include "lib/chrono_timer.hpp"
#include "material/material.hpp"
#include "maths/constants.hpp"

void camera::render(const hittable_list& world, const std::string& output_filename) {
    initialize_camera();

    Image canvas(image_width, image_height);

    Chrono render_timer;
    render_timer.start();

    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0)
        num_threads = 4;

    std::cout << "Rendering with " << num_threads << " threads..." << std::endl;

    std::vector<std::thread> threads;
    std::atomic<int> next_line(0);

    auto render_lines = [&]() {
        while (true) {
            int y = next_line.fetch_add(1);
            if (y >= image_height)
                break;

            for (int x = 0; x < image_width; ++x) {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(x, y);
                    pixel_color += ray_color(r, max_depth, world);
                }

                color final_color = pixel_samples_scale * pixel_color;
                canvas.SetPixel(x, image_height - 1 - y, final_color);
            }
        }
    };

    for (unsigned int i = 0; i < num_threads; ++i) {
        threads.emplace_back(render_lines);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    canvas.WriteFile(output_filename.c_str());
    render_timer.log("Rendering finished");
}

void camera::initialize_camera() {
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0f / samples_per_pixel;

    float actual_aspect_ratio = image_width / static_cast<float>(image_height);
    auto theta = degrees_to_radians(vfov);
    auto h = std::tan(theta / 2);

    auto viewport_height = 2.0 * h * focal_length;
    viewport_width = actual_aspect_ratio * viewport_height;
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
    color deep_space = color(0.2f, 0.2f, 0.5f);
    color space_blue = color(0.3f, 0.3f, 0.5f);
    return (1.0f - t) * deep_space + t * space_blue;
}

color camera::ray_color(const ray& r, int depth, const hittable_list& world) const {
    HitRecord rec;
    interval ray_t(0.00001f, infinity);
    if (depth <= 0)
        return color(0, 0, 0);

    if (world.hit(r, ray_t, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, depth - 1, world);
        return color(0, 0, 0);
    }

    return background_color(r);
}

ray camera::get_ray(int i, int j) const {
    auto offset = sample_square();

    auto pixel_sample =
        first_pixel_center + ((i + offset.x()) * pixel_step_u) + ((j + offset.y()) * pixel_step_v);

    auto ray_origin = camera_origin;
    auto ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
}

vector3 camera::sample_square() const {
    return vector3(random_float() - 0.5f, random_float() - 0.5f, 0);
}
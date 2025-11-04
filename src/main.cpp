#include <iostream>

#include "core/color.hpp"
#include "core/ray.hpp"
#include "image/image.hpp"
#include "maths/vector3.hpp"
#include "timer/chrono_timer.hpp"

int main(int, char**) {
    std::cout << "Hello, from rayborn!\n";

    // Test 1: vector3
    vector3 v1(1.0f, 3.0f, 3.0f);
    vector3 v2(4.0f, 5.0f, 6.0f);
    vector3 v3 = v1 * v2;
    std::cout << "v1 * v2 = " << v3 << std::endl;
    std::cout << "length of v1: " << v1.length() << std::endl;

    // Test 2: create image with simple gradien as in the book
    std::cout << "\nCreating test image...\n";
    Chrono timer;

    timer.start();

    // image information
    auto aspect_ratio = 16.0f / 9.0f;
    int image_width = 1080;

    int image_height = static_cast<int>(image_width / aspect_ratio);
    std::cout << " imga height" << image_height << std::endl;

    image_height = (image_height < 1) ? 1 : image_height;

    // camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto image_real_ratio = float(image_width) / float(image_height);
    auto viewport_width = image_real_ratio * viewport_height;
    auto camera_center = point3(0, 0, 0);

    // vectors for camera like  u and v ( horizontal /vectical)
    auto viewport_u = vector3(viewport_width, 0, 0);
    auto viewport_v = vector3(0, viewport_height, 0);

    // calculate for each pixel the ray from the camera origin to the pixel position on the viewport
    auto pixel_delta_u = viewport_u / (image_width);
    auto pixel_delta_v = viewport_v / (image_height);

    // top left of the viewport in world space
    auto viewport_top_left =
        camera_center - vector3(viewport_width * 0.5, viewport_height * 0.5, focal_length);

    auto first_pixel_center = viewport_top_left + 0.5f * (pixel_delta_u + pixel_delta_v);

    Image img(image_width, image_height);

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            auto pixel_position =
                first_pixel_center + float(i) * pixel_delta_u + float(j) * pixel_delta_v;

            auto ray_direction = pixel_position - camera_center;

            ray r(camera_center, ray_direction);

            color pixel = ray_color(r);

            img.SetPixel(i, j, pixel);
        }
    }

    img.WriteFile("tesssttttt.png");

    timer.log("Temps de rendu");

    std::cout << "All modules loaded successfully!\n";
    return 0;
}

#include <iostream>

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
    Image img(256, 256);

    for (unsigned int j = 0; j < 256; ++j) {
        for (unsigned int i = 0; i < 256; ++i) {
            color pixel(float(i) / 255.0f, float(j) / 255.0f, 0.25f);
            img.SetPixel(i, j, pixel);
        }
    }
     
    std::cout << "Modules ready. Starting render now...\n";

    Chrono timer;

    timer.start();

    img.WriteFile("tesssttttt.png");

    timer.log("Temps de rendu");

    std::cout << "All modules loaded successfully!\n";
    return 0;
}

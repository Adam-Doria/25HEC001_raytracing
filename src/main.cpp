#include <iostream>

#include "core/ray.hpp"
#include "image/image.hpp"
#include "maths/vector3.cpp"

int main(int, char**) {
    std::cout << "Hello, from rayborn!\n";

    // maths::initMaths();
    // test vector3
    vector3 v1(1.0f, 3.0f, 3.0f);
    vector3 v2(4.0f, 5.0f, 6.0f);
    vector3 v3 = v1 * v2;
    std::cout << "v1 *v2 = " << v3 << std::endl;

    // test length
    std::cout << "length of v1: " << v1.length() << std::endl;

    core::initCore();
    image::initImage();

    std::cout << "All modules loaded successfully!\n";
    return 0;
}

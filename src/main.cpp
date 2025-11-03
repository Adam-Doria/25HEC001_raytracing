#include <iostream>
#include "maths/vector3.hpp"
#include "core/ray.hpp"
#include "image/image.hpp"

int main(int, char**){
    std::cout << "Hello, from rayborn!\n";
    
    maths::initMaths();
    core::initCore();
    image::initImage();
    
    std::cout << "All modules loaded successfully!\n";
    return 0;
}

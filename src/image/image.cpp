#include "image.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

#include "lodepng/lodepng.h"

Image::Image(unsigned int w, unsigned int h) : width(w), height(h) {
    buffer.resize(width * height);
    for (int i = 0; i < buffer.size(); ++i) {
        buffer[i] = color(0, 0, 0);
    }
}

Image::Image(unsigned int w, unsigned int h, color c) : width(w), height(h) {
    buffer.resize(width * height);
    for (int i = 0; i < buffer.size(); ++i) {
        buffer[i] = c;
    }
}

Image::~Image() {}

void Image::SetPixel(unsigned int x, unsigned int y, color pixel_color) {
    unsigned int index = (y * width) + x;

    if (index >= buffer.size()) {
        throw std::invalid_argument("Image::SetPixel: Invalid coordinates");
    }
    buffer[index] = pixel_color;
}

color Image::GetPixel(unsigned int x, unsigned int y) {
    unsigned int index = (y * width) + x;

    if (index >= buffer.size()) {
        throw std::invalid_argument("Image::GetPixel: Invalid coordinates");
    }
    return buffer[index];
}

void Image::WriteFile(const char* filename) {
    std::vector<unsigned char> image;
    image.resize(width * height * 4);

    for (unsigned index = 0; index < buffer.size(); index++) {
        color pixel = buffer[index];
        int offset = index * 4;

        image[offset] = static_cast<unsigned char>(std::floor(pixel.x() * 255.999));      // R
        image[offset + 1] = static_cast<unsigned char>(std::floor(pixel.y() * 255.999));  // G
        image[offset + 2] = static_cast<unsigned char>(std::floor(pixel.z() * 255.999));  // B
        image[offset + 3] = 255;  // Alpha (opaque)
    }

    unsigned error = lodepng::encode(filename, image, width, height);

    if (error) {
        std::cerr << "PNG encoder error " << error << ": " << lodepng_error_text(error)
                  << std::endl;
    }
}

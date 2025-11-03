#pragma once

#include <cmath>
#include <iostream>

class vector3 {
public:
    float element[3];

    vector3() : element{0, 0, 0} {}
    vector3(float element0, float element1, float element2)
        : element{element0, element1, element2} {}

    float x() const {
        return element[0];
    }
    float y() const {
        return element[1];
    }
    float z() const {
        return element[2];
    }

    vector3 operator-() const {
        return vector3(-element[0], -element[1], -element[2]);
    }
    float operator[](int i) const {
        return element[i];
    }  // lecture
    float& operator[](int i) {
        return element[i];
    }  // écriture

    vector3& operator+=(const vector3& v) {
        element[0] += v.element[0];
        element[1] += v.element[1];
        element[2] += v.element[2];
        return *this;
    }

    vector3& operator*=(const float t) {
        element[0] *= t;
        element[1] *= t;
        element[2] *= t;
        return *this;
    }
    vector3& operator/=(const float t) {
        return *this *= 1 / t;
    }

    float length() const {
        return std::sqrt(length_squared());
    }

    float length_squared() const {
        return element[0] * element[0] + element[1] * element[1] + element[2] * element[2];
    }
};
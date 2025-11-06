#pragma once

#include <cmath>
#include <iostream>

#include "constants.hpp"

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
        float inv = 1.0f / t;
        return *this *= inv;
    }

    float length() const {
        return std::sqrt(length_squared());
    }

    float length_squared() const {
        return element[0] * element[0] + element[1] * element[1] + element[2] * element[2];
    }

    float inv_length() const {
        return 1.0f / std::sqrt(length_squared());
    }

    static vector3 random() {
        return vector3(random_float(), random_float(), random_float());
    }
    static vector3 random(float min, float max) {
        return vector3(random_float(min, max), random_float(min, max), random_float(min, max));
    }

    bool near_zero() const {
        auto s = 1e-8;
        return (std::fabs(element[0]) < s) && (std::fabs(element[1]) < s) &&
               (std::fabs(element[2]) < s);
    }
};

using point3 = vector3;  // 3D point
using color = vector3;   // RGB color

inline std::ostream& operator<<(std::ostream& out, const vector3& v) {
    return out << v.element[0] << ' ' << v.element[1] << ' ' << v.element[2];
}

inline vector3 operator+(const vector3& u, const vector3& v) {
    return vector3(u.element[0] + v.element[0], u.element[1] + v.element[1],
                   u.element[2] + v.element[2]);
}
inline vector3 operator-(const vector3& u, const vector3& v) {
    return vector3(u.element[0] - v.element[0], u.element[1] - v.element[1],
                   u.element[2] - v.element[2]);
}
inline vector3 operator*(const vector3& u, const vector3& v) {
    return vector3(u.element[0] * v.element[0], u.element[1] * v.element[1],
                   u.element[2] * v.element[2]);
}
inline vector3 operator*(float t, const vector3& v) {
    return vector3(t * v.element[0], t * v.element[1], t * v.element[2]);
}
inline vector3 operator*(const vector3& v, float t) {
    return t * v;
}
inline vector3 operator/(const vector3& v, float t) {
    float inv = 1.0f / t;
    return inv * v;
}
inline float dot(const vector3& u, const vector3& v) {
    return u.element[0] * v.element[0] + u.element[1] * v.element[1] + u.element[2] * v.element[2];
}
inline vector3 cross(const vector3& u, const vector3& v) {
    return vector3(u.element[1] * v.element[2] - u.element[2] * v.element[1],
                   u.element[2] * v.element[0] - u.element[0] * v.element[2],
                   u.element[0] * v.element[1] - u.element[1] * v.element[0]);
}
inline vector3 unit_vector(const vector3& v) {
    float inv_len = v.inv_length();
    return inv_len * v;
}

inline vector3 random_unit_vector() {
    while (true) {
        vector3 p = vector3::random(-1.0f, 1.0f);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}

inline vector3 random_in_hemisphere(const vector3& normal) {
    vector3 in_unit_sphere = random_unit_vector();
    if (dot(in_unit_sphere, normal) > 0.0f)
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

inline vector3 reflect(const vector3& v, const vector3& n) {
    return v - 2 * dot(v, n) * n;
}
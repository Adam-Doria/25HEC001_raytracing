#include "vector3.hpp"

#include <iostream>

std::ostream& operator<<(std::ostream& out, const vector3& v) {
    return out << v.element[0] << ' ' << v.element[1] << ' ' << v.element[2];
}
vector3 operator+(const vector3& u, const vector3& v) {
    return vector3(u.element[0] + v.element[0], u.element[1] + v.element[1],
                   u.element[2] + v.element[2]);
}
vector3 operator-(const vector3& u, const vector3& v) {
    return vector3(u.element[0] - v.element[0], u.element[1] - v.element[1],
                   u.element[2] - v.element[2]);
}
vector3 operator*(const vector3& u, const vector3& v) {
    return vector3(u.element[0] * v.element[0], u.element[1] * v.element[1],
                   u.element[2] * v.element[2]);
}
vector3 operator*(float t, const vector3& v) {
    return vector3(t * v.element[0], t * v.element[1], t * v.element[2]);
}
vector3 operator*(const vector3& v, float t) {
    return t * v;
}
vector3 operator/(vector3 v, float t) {
    return (1 / t) * v;
}

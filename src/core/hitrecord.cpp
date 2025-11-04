#include "hitrecord.hpp"

#include <iomanip>
#include <iostream>

void HitRecord::set_face_normal(const ray& r, const vector3& outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
}

void HitRecord::log(const std::string& message) {
    std::cout << message << " at t=" << std::fixed << std::setprecision(6) << t << " p=(" << p.x()
              << "," << p.y() << "," << p.z() << ")"
              << "\n";
}

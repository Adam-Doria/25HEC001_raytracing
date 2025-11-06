#pragma once

#include "lib/lib.hpp"

/**
 * @file plane.hpp
 * @brief Defines a geometric plane shape.
 */

class ray;
class HitRecord;
class interval;

#include "core/hittable.hpp"
#include "material/material.hpp"

/**
 * @brief Infinite plane represented by a point and a normal.
 */
class plane : public Hittable {
public:
    plane(const point3& point_on_plane, const vector3& normal_vector,
          shared_ptr<material> material);

    bool hit(const ray& r, interval ray_t, HitRecord& rec) const override;

private:
    point3 point;
    vector3 normal;
    shared_ptr<material> mat;
};

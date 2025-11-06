#pragma once

#include "lib/lib.hpp"

/**
 * @file triangle.hpp
 * @brief
 */

class ray;
class HitRecord;
class interval;

#include "core/hittable.hpp"
#include "material/material.hpp"

/**
 * @brief
 *
 * Le triangle est défini par ses trois sommets (v0, v1, v2).
 */
class triangle : public Hittable {
public:
    /**
     * @brief
     *
     * @param v0
     * @param v1
     * @param v2
     * @param material
     */
    triangle(const point3& v0, const point3& v1, const point3& v2, shared_ptr<material> material);

    /**
     * @brief
     *
     *
     * @param r
     * @param ray_t
     *
     * @param rec
     * @return
     */
    bool hit(const ray& r, interval ray_t, HitRecord& rec) const override;

    aabb bounding_box() const override {
        return bbox;
    }

private:
    point3 v0, v1, v2;
    vector3 normal;
    shared_ptr<material> mat;
    aabb bbox;
};

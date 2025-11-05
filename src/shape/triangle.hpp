#pragma once

/**
 * @file triangle.hpp
 * @brief
 */

class ray;
class HitRecord;
class interval;

#include "core/hittable.hpp"
#include "maths/vector3.hpp"

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
     */
    triangle(const point3& v0, const point3& v1, const point3& v2);

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

private:
    point3 v0, v1, v2;
    vector3 normal;
};

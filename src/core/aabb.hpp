#pragma once

#include "lib/lib.hpp"

class aabb {
public:
    interval x, y, z;

    aabb() {}

    aabb(const interval& x, const interval& y, const interval& z) : x(x), y(y), z(z) {}

    aabb(const point3& a, const point3& b) {
        x = (a[0] < b[0]) ? interval(a[0], b[0]) : interval(b[0], a[0]);
        y = (a[1] < b[1]) ? interval(a[1], b[1]) : interval(b[1], a[1]);
        z = (a[2] < b[2]) ? interval(a[2], b[2]) : interval(b[2], a[2]);
    }

    const interval& get_axis_interval(int axis) const {
        if (axis == 1)
            return y;
        if (axis == 2)
            return z;
        return x;
    }

    bool hit(const ray& r, interval ray_t) const {
        const point3& origin = r.origin();
        const vector3& direction = r.direction();

        for (int axis = 0; axis < 3; axis++) {
            const interval& axis_interval = get_axis_interval(axis);
            const float inverse_direction = 1.0f / direction[axis];

            auto t0 = (axis_interval.min - origin[axis]) * inverse_direction;
            auto t1 = (axis_interval.max - origin[axis]) * inverse_direction;

            if (t0 < t1) {
                if (t0 > ray_t.min)
                    ray_t.min = t0;
                if (t1 < ray_t.max)
                    ray_t.max = t1;
            } else {
                if (t1 > ray_t.min)
                    ray_t.min = t1;
                if (t0 < ray_t.max)
                    ray_t.max = t0;
            }

            if (ray_t.max <= ray_t.min)
                return false;
        }
        return true;
    }

    aabb(const aabb& box0, const aabb& box1) {
        x = interval(box0.x, box1.x);
        y = interval(box0.y, box1.y);
        z = interval(box0.z, box1.z);
    }
};
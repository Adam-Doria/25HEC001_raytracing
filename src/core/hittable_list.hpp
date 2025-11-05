#pragma once

#include <vector>

#include "hitrecord.hpp"
#include "hittable.hpp"
#include "lib/lib.hpp"
#include "ray.hpp"

class hittable_list : public Hittable {
public:
    std::vector<shared_ptr<Hittable>> objects;

    hittable_list() {}
    hittable_list(shared_ptr<Hittable> object) {
        add(object);
    }
    void clear() {
        objects.clear();
    }
    void add(shared_ptr<Hittable> object) {
        objects.push_back(object);
    }

    bool hit(const ray& r, interval ray_t, HitRecord& rec) const override {
        HitRecord temp_rec;
        bool hit_anything = false;
        float closest_so_far = ray_t.max;

        for (const auto& object : objects) {
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};
#include "material.hpp"

#include "core/hitrecord.hpp"

class lambertian : public material {
public:
    lambertian(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,
                 ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        scattered = ray(rec.p, scatter_direction);
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};
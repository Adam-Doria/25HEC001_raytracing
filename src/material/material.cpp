#include "material.hpp"

#include "core/hitrecord.hpp"
#include "core/ray.hpp"
#include "maths/vector3.hpp"

// Lambertian material
lambertian::lambertian(const color& albedo) : albedo(albedo) {}

bool lambertian::scatter(const ray& r_in, const HitRecord& rec, color& attenuation,
                         ray& scattered) const {
    auto scatter_direction = rec.normal + random_unit_vector();
    if (scatter_direction.near_zero())
        scatter_direction = rec.normal;
    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

// Metal material
metal::metal(const color& albedo) : albedo(albedo) {}

bool metal::scatter(const ray& r_in, const HitRecord& rec, color& attenuation,
                    ray& scattered) const {
    vector3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return true;
}
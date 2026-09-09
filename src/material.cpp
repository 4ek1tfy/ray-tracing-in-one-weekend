#include "material.hpp"

material::~material() = default;

bool material::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
    return false;
}

lambertian::lambertian(const color& _albedo) : albedo(_albedo) {}

bool lambertian::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
    auto scatter_direction = rec.normal + random_unit_vector();

    if(scatter_direction.near_zero()){
        scatter_direction = rec.normal;
    }

    scattered = ray(rec.p, scatter_direction, r_in.time());
    attenuation = albedo;
    return true;
}

metal::metal(const color& _albedo, double _fuzz) : albedo(_albedo), fuzz(_fuzz < 1 ? _fuzz : 1) {}

bool metal::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
    vec3 reflected = reflect(r_in.direction(), rec.normal);

    reflected = unit_vector(reflected) + (fuzz * random_unit_vector());

    scattered = ray(rec.p, reflected, r_in.time());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

dielectric::dielectric(double _refraction_index) : refraction_index(_refraction_index == 0? 0.001 : _refraction_index) {}

bool dielectric::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
    attenuation = color(1.0, 1.0, 1.0);
    double ri = rec.front_face ? (1.0/refraction_index) : refraction_index;

    vec3 unit_direction = unit_vector(r_in.direction());
    
    double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;
    vec3 direction;

    if (cannot_refract || reflectance(cos_theta, ri) > random_double())
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, ri);

    scattered = ray(rec.p, direction, r_in.time());
    return true;
}

double dielectric::reflectance(double cosine, double refraction_index) {
    auto r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0*r0;
    return r0 + (1-r0)*std::pow((1 - cosine),5);
}
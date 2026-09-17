#pragma once
#include "ray.hpp"
#include "vec3.hpp"
#include "hittable.hpp"
#include "color.hpp"
#include "texture.hpp"

class material{
public:
    virtual ~material();

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const;

    virtual color emitted(double u, double v, const point3& p) const {
        return color(0, 0, 0);
    }
};

class lambertian : public material{
public:
    lambertian(const color& albedo);

    lambertian(std::shared_ptr<texture> _tex);

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

private:
    std::shared_ptr<texture> tex;
};

class metal : public material{
public:
    metal(const color& _albedo, double _fuzz);

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

private:
    color albedo;
    double fuzz;
};

class dielectric : public material {
public:
    dielectric(double _refraction_index);

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

private:
    double refraction_index;

    static double reflectance(double cosine, double refraction_index);
};

class diffuse_light : public material {
public:
    diffuse_light(std::shared_ptr<texture> _tex) : tex(std::move(_tex)) {}
    diffuse_light(const color& emit) : tex(std::make_shared<solid_color>(emit)) {}

    color emitted(double u, double v, const point3& p) const override {
        return tex->value(u, v, p);
    }

private:
    std::shared_ptr<texture> tex;
};


class isotropic : public material {
public:
    isotropic(const color& albedo);
    isotropic(std::shared_ptr<texture> _tex);

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

private:
    std::shared_ptr<texture> tex;
};
#pragma once
#include "vec3.hpp"
#include "color.hpp"
#include "rtw_stb_image.hpp"
#include "perlin.hpp"

#include <memory>

class texture{
public:
    virtual ~texture();

    virtual color value(double u, double v, const point3& p) const = 0;
};

class solid_color : public texture{
public:
    solid_color(const color& _albedo);

    solid_color(double red, double green, double blue);

    color value(double u, double v, const point3& p) const override;

private:
    color albedo;
};

class checker_texture : public texture{
public:
    checker_texture(double scale, std::shared_ptr<texture> _even, std::shared_ptr<texture> _odd);

    checker_texture(double scale, const color& c1, const color& c2);

    color value(double u, double v, const point3& p) const override;

private:
    double inv_scale;
    std::shared_ptr<texture> even;
    std::shared_ptr<texture> odd;
};

class image_texture : public texture {
public:
    image_texture(const char* filename);

    color value(double u, double v, const point3& p) const override;

private:
    rtw_image image;
};

class noise_texture : public texture {
public:
    noise_texture(double _scale);

    color value(double u, double v, const point3& p) const override;

private:
    perlin noise;
    double scale;
};
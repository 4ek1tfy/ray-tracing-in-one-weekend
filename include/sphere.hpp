#pragma once
#include "hittable.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "aabb.hpp"

#include <memory>

class sphere : public hittable{
public:
    sphere(const point3& static_center, double _radius, std::shared_ptr<material> _mat);

    sphere(const point3& center1, const point3& center2, double radius, std::shared_ptr<material> mat);
    
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

    aabb bounding_box() const override;

private:
    ray center;
    double radius;
    std::shared_ptr<material> mat;
    aabb bbox;
};
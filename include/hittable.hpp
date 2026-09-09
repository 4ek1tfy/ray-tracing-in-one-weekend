#pragma once
#include "vec3.hpp"
#include "ray.hpp"
#include "interval.hpp"
#include "aabb.hpp"

#include <memory>

class material;

class hit_record{
public:
    point3 p;
    vec3 normal;
    std::shared_ptr<material> mat;
    double t;
    bool front_face;

    void set_face_normal(const ray& r, vec3& outward_normal);
};

class hittable{
public:
    virtual ~hittable();

    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;

    virtual aabb bounding_box() const = 0;
};
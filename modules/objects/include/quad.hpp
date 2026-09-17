#pragma once
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "vec3.hpp"
#include "material.hpp"
#include "aabb.hpp"

#include <memory>

class quad : public hittable{
public:
    quad(const point3& _Q, const vec3& _u, const vec3& _v, std::shared_ptr<material> _mat);
    
    virtual void set_bounding_box();
    
    aabb bounding_box() const override;

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

    virtual bool is_interior(double a, double b, hit_record& rec) const;

private:
    point3 Q;  
    vec3 u; 
    vec3 v;
    vec3 w;
    std::shared_ptr<material> mat;
    aabb bbox;
    vec3 normal;
    double D;
};

inline std::shared_ptr<hittable_list> box(const point3& a, const point3& b, std::shared_ptr<material> mat){
    auto sides = std::make_shared<hittable_list>();

    auto min = point3(std::fmin(a.x(),b.x()), std::fmin(a.y(),b.y()), std::fmin(a.z(),b.z()));
    auto max = point3(std::fmax(a.x(),b.x()), std::fmax(a.y(),b.y()), std::fmax(a.z(),b.z()));

    auto dx = vec3(max.x() - min.x(), 0, 0);
    auto dy = vec3(0, max.y() - min.y(), 0);
    auto dz = vec3(0, 0, max.z() - min.z());

    sides->add(std::make_shared<quad>(point3(min.x(), min.y(), max.z()),  dx,  dy, mat)); // front
    sides->add(std::make_shared<quad>(point3(max.x(), min.y(), max.z()), -dz,  dy, mat)); // right
    sides->add(std::make_shared<quad>(point3(max.x(), min.y(), min.z()), -dx,  dy, mat)); // back
    sides->add(std::make_shared<quad>(point3(min.x(), min.y(), min.z()),  dz,  dy, mat)); // left
    sides->add(std::make_shared<quad>(point3(min.x(), max.y(), max.z()),  dx, -dz, mat)); // top
    sides->add(std::make_shared<quad>(point3(min.x(), min.y(), min.z()),  dx,  dz, mat)); // bottom

    return sides;
}
#pragma once
#include "hittable.hpp"
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
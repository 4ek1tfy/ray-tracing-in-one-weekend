#include "hittable.hpp"

void hit_record::set_face_normal(const ray& r, const vec3& outward_normal){
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
}

hittable::~hittable() = default;

translate::translate(std::shared_ptr<hittable> _object, const vec3& _offset)
    : object(std::move(_object)), offset(_offset)
{
    bbox = object->bounding_box() + offset;
}

bool translate::hit(const ray& r, interval ray_t, hit_record& rec) const {
    ray offset_r(r.origin() - offset, r.direction(), r.time());
    if (!object->hit(offset_r, ray_t, rec))
        return false;
    rec.p += offset;

    return true;
}

aabb translate::bounding_box() const { return bbox;}

rotate_y::rotate_y(std::shared_ptr<hittable> _object, double angle) : object(std::move(_object)) {
    auto radians = degrees_to_radians(angle);
    sin_theta = std::sin(radians);
    cos_theta = std::cos(radians);
    bbox = object->bounding_box();

    point3 min( infinity,  infinity,  infinity);
    point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i*bbox.x.max + (1-i)*bbox.x.min;
                auto y = j*bbox.y.max + (1-j)*bbox.y.min;
                auto z = k*bbox.z.max + (1-k)*bbox.z.min;

                auto newx =  cos_theta*x + sin_theta*z;
                auto newz = -sin_theta*x + cos_theta*z;

                vec3 tester(newx, y, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = std::fmin(min[c], tester[c]);
                    max[c] = std::fmax(max[c], tester[c]);
                }
            }
        }
    }

    bbox = aabb(min, max);
}

bool rotate_y::hit(const ray& r, interval ray_t, hit_record& rec) const {
    auto origin = point3(
        (cos_theta * r.origin().x()) - (sin_theta * r.origin().z()),
        r.origin().y(),
        (sin_theta * r.origin().x()) + (cos_theta * r.origin().z())
    );

    auto direction = vec3(
        (cos_theta * r.direction().x()) - (sin_theta * r.direction().z()),
        r.direction().y(),
        (sin_theta * r.direction().x()) + (cos_theta * r.direction().z())
    );

    ray rotated_r(origin, direction, r.time());

    if (!object->hit(rotated_r, ray_t, rec))
        return false;

    rec.p = point3(
        (cos_theta * rec.p.x()) + (sin_theta * rec.p.z()),
        rec.p.y(),
        (-sin_theta * rec.p.x()) + (cos_theta * rec.p.z())
    );

    rec.normal = vec3(
        (cos_theta * rec.normal.x()) + (sin_theta * rec.normal.z()),
        rec.normal.y(),
        (-sin_theta * rec.normal.x()) + (cos_theta * rec.normal.z())
    );

    return true;
}

aabb rotate_y::bounding_box() const { return bbox;}
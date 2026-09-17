#include "hittable.hpp"
#include "vec3.hpp"
#include "material.hpp"

#include <memory>


class constant_medium : public hittable {
public:
    constant_medium(std::shared_ptr<hittable> _boundary, double density, std::shared_ptr<texture> tex);

    constant_medium(std::shared_ptr<hittable> _boundary, double density, const color& albedo);

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

    aabb bounding_box() const override;

private:
    std::shared_ptr<hittable> boundary;
    double neg_inv_density;
    std::shared_ptr<material> phase_function;
};

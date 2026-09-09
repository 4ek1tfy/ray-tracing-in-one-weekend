#pragma once
#include "aabb.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "interval.hpp"
#include "ray.hpp"

#include <memory>

class bvh_node : public hittable {
public:
    bvh_node(hittable_list list);

    bvh_node(std::vector<std::shared_ptr<hittable>>& objects, size_t start, size_t end);

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

    aabb bounding_box() const override;

private:
    std::shared_ptr<hittable> left;
    std::shared_ptr<hittable> right;
    aabb bbox;

    static bool box_compare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b, int axis_index);

    static bool box_x_compare (const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b);

    static bool box_y_compare (const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b);

    static bool box_z_compare (const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b);
};
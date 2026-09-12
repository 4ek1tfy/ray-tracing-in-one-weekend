#pragma once
#include "vec3.hpp"

class ray{
private:
    point3 orig;
    vec3 dir;
    double tm;

public:
    ray();

    ray(const point3& origin, const vec3& direction, double time);

    ray(const point3& origin, const vec3& direction);

    const point3& origin() const;
    const vec3& direction() const;
    double time() const;

    point3 at(const double t) const;
};

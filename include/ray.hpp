#pragma once

#include <vec3.hpp>
#include <color.hpp>

class ray{
private:
    point3 orig;
    vec3 dir;

public:
    ray(){}

    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    const point3& origin() {return orig;}
    const vec3& direction() {return dir;}

    point3 at(const double t) const {
        return orig + dir * t;
    }
};

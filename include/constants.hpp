#pragma once

#include <iostream>
#include <cmath>
#include <limits>
#include <memory>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "interval.hpp"
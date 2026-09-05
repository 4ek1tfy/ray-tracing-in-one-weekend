#pragma once

#include <iostream>
#include <cmath>
#include <limits>
#include <memory>
#include <random>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}

#include "vec3.hpp"
#include "ray.hpp"
#include "interval.hpp"
#include "color.hpp"
#include "hittable.hpp"
#include "material.hpp"
#pragma once
#include "constants.hpp"

class interval{
public:
    double min, max;

    interval();

    interval(double _min, double _max);

    interval(const interval& a, const interval& b);

    double size() const;

    bool contains(double x) const;

    bool surrounds(double x) const;

    double clamp(double x) const;

    interval expand(double delta);

    static const interval empty, universe;
};
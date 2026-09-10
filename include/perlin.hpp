#pragma once
#include "vec3.hpp"

class perlin {
  public:
    perlin();

    double noise(const point3& p) const;

  private:
    static const int point_count = 256;
    double randfloat[point_count];
    int perm_x[point_count];
    int perm_y[point_count];
    int perm_z[point_count];

    static void perlin_generate_perm(int* p);

    static void permute(int* p, int n);
};
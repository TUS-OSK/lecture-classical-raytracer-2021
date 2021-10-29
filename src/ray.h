#ifndef _RAY_H
#define _RAY_H
#include "vec3.h"

struct Ray {
  Vec3f origin;
  Vec3f direction;
  float rayMin = 1e-3;
  float rayMax = 10000.0;

  Ray(const Vec3f &origin, const Vec3f &direction)
      : origin(origin), direction(direction) {}

  Vec3f posT(float t) const { return origin + t * direction; }
};
#endif
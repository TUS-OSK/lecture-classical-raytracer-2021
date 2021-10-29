#pragma once
#include <cmath>

#include "intersectinfo.h"
#include "ray.h"
#include "vec3.h"

enum Material {
  Diffuse,
  Mirror,
  Glass,
  Emmition,
};

class Sphere {
 private:
  Vec3f pos;
  float r;
  Material material;
  Vec3f color;

 public:
  Sphere(Vec3f p, float r) : pos(p), r(r) {
    material = Material::Diffuse;
    color = Vec3f(1.0);
  }
  Sphere(Vec3f p, float r, Material mat, Vec3f c)
      : pos(p), r(r), material(mat), color(c) {}

  bool hit(const Ray &ray, IntersectInfo &info) {
    float b = dot(ray.direction, ray.origin - pos);
    float c = nolm2(ray.origin - pos) - (r * r);

    float D = b * b - c;
    if (D < 0) return false;

    float t1 = -b - std::sqrt(D);
    float t2 = -b + std::sqrt(D);

    float t = t1;

    if (t < ray.rayMin || t > ray.rayMax) {
      t = t2;
      if (t2 < ray.rayMin || t > ray.rayMax) {
        return false;
      }
    }

    float distance = t;
    Vec3f position = ray.posT(t);
    Vec3f normal = normalize(position - pos);

    info.distance = distance;
    info.position = position;
    info.normal = normal;
    info.sphere = this;

    return true;
  }

  Material getMaterial() const { return material; }
  Vec3f getColor() const { return color; }
};
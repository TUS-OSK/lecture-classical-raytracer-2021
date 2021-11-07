#pragma once

#include "intersectinfo.h"
#include "ray.h"
#include "vec3.h"

enum Material {
  Diffuse,
  Mirror,
  Glass,
  Emmition,
};
struct IntersectInfo;

class Shape{
    public:
    virtual bool hit(const Ray& ray,IntersectInfo& info) = 0; 
    virtual Material getMaterial()const = 0; 
    virtual Vec3f getColor()const = 0; 
};
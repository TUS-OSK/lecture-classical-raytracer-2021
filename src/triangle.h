#pragma once
#include <iostream>
#include "shape.h"
#include "vec3.h"
class Triangle: public Shape{
    private:
    Vec3f p[3];
    Material mat;
    Vec3f color;

    public:
    Triangle(const Vec3f& p0,const Vec3f& p1,const Vec3f& p2,const Material& mat,const Vec3f& color):mat(mat),color(color){
        p[0] = p0;
        p[1] = p1;
        p[2] = p2;
    }

    bool hit(const Ray& ray,IntersectInfo& info) override{
        Vec3f e1 = p[1] - p[0];
        Vec3f e2 = p[2] - p[0];

        Vec3f r = ray.origin - p[0];
        Vec3f alpha = cross(ray.direction,e2);
        Vec3f beta = cross(r,e1);

        float det = dot(alpha,e1);
        float EPS = ray.rayMin;
        if(-EPS < det && EPS > det) return false;

        float u = dot(alpha,r) / det;
        if(u < 0 || u > 1.0) return false;

        float v = dot(beta,ray.direction) /det;
        if(v < 0 || v + u > 1.0) return false;

        float t = dot(beta,e2) / det;
        if(t < ray.rayMin || t > ray.rayMax) return false;

        info.distance = t;
        info.normal = normalize(cross(e1,e2));
        info.position = ray.posT(t);
        info.sphere = this;
        std::cout << "distance" << info.distance << std::endl;
        std::cout << "normal" << info.normal << std::endl;
        std::cout << "position" << info.position << std::endl;
        std::cout << "t" << t << std::endl;
        std::cout << "u" << u << std::endl;
        std::cout << "v" << v << std::endl;
        std::cout << "p0" << p[0] << std::endl;
        std::cout << "p1" << p[1] << std::endl;
        std::cout << "p2" << p[2] << std::endl;
        std::cout << "e1" << e1 << std::endl;
        std::cout << "e2" << e2 << std::endl;
        std::cout << "det" << det << std::endl;
        std::cout << "alpha" << alpha << std::endl;
        std::cout << "beta" << beta << std::endl;
        std::cout << "raydirection" << ray.direction << std::endl;
        std::cout << "rayorigin" << ray.origin << std::endl;
        return true;
    }

  Material getMaterial() const override{ return mat; }
  Vec3f getColor() const override{ return color; }
};
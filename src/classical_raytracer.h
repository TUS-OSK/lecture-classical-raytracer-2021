#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>

#include "intersectinfo.h"
#include "ray.h"
#include "rng.h"
#include "scene.h"
#include "sphere.h"
#include "vec3.h"
#define Pi 3.141592

Vec3f WorldtoLocal(const Vec3f &t, const Vec3f &n, const Vec3f &b,
                   const Vec3f &p) {
  return Vec3f(t[0] * p[0] + t[1] * p[1] + t[2] * p[2],
               n[0] * p[0] + n[1] * p[1] + n[2] * p[2],
               b[0] * p[0] + b[1] * p[1] + b[2] * p[2]);
}
Vec3f LocaltoWorld(const Vec3f &t, const Vec3f &n, const Vec3f &b,
                   const Vec3f &p) {
  return Vec3f(t[0] * p[0] + n[0] * p[1] + b[0] * p[2],
               t[1] * p[0] + n[1] * p[1] + b[1] * p[2],
               t[2] * p[0] + n[2] * p[1] + b[2] * p[2]);
}

Vec3f SphereSampling(const float u, const float v) {
  float theta = std::acos(std::max(1.0f - u, 0.0f));
  float phi = 2.0f * Pi * v;
  return Vec3f(std::cos(phi) * std::sin(theta), std::max(1.0f - u, 0.0f),
               std::sin(phi) * std::sin(theta));
}

float RTAO(Scene &scene, const IntersectInfo &info, RNGrandom &rng) {
  //サンプル数
  const int AO_SAMPLING = 100;
  //遮蔽の距離
  const float DISTANCE = 10.0f;

  //接空間の基底ベクトル
  Vec3f t, b;
  if (info.normal[1] < 0.9f) {
    t = normalize(cross(info.normal, Vec3f(0, 1, 0)));
  } else {
    t = normalize(cross(info.normal, Vec3f(0, 0, -1)));
  }
  b = normalize(cross(t, info.normal));

  float counter = 0;
  for (int i = 0; i < AO_SAMPLING; i++) {
    const Vec3f target_direction =
        SphereSampling(rng.getRandom(), rng.getRandom());

    const Vec3f direction = LocaltoWorld(t, info.normal, b, target_direction);
    Ray shadow_ray(info.position + direction * 0.01f, direction);
    IntersectInfo shadow_info;
    if (scene.hit(shadow_ray, shadow_info) && shadow_info.distance < DISTANCE) {
      counter++;
    }
  }

  return counter / AO_SAMPLING;
}

Vec3f Classical_Raytracer(const Ray &r, Scene &scene, RNGrandom &rng) {
  Ray ray = r;
  const int Max = 100;
  Vec3f Light = normalize(Vec3f(1.0, 1.0, 0.0));
  Vec3f col;
  for (int i = 0; i < Max; i++) {
    IntersectInfo info;
    if (scene.hit(ray, info)) {
      Material mat = info.sphere->getMaterial();
      // std::cout << mat << std::endl;
      //       std::cout << "test" << std::endl;
      if (mat == Material::Mirror) {
        Vec3f r = normalize(reflection(-1.0f * ray.direction, info.normal));
        ray = Ray(info.position, r);
      } else if (mat == Material::Glass) {
        float n1 = 1.0, n2 = 1.5;
        bool is_inside = dot(-1.0f * ray.direction, info.normal) < 0.0f;

        if (is_inside) {
          n1 = 1.5;
          n2 = 1.0;
        }

        Vec3f r;
        if (!is_inside) {
          if (!refraction(-1.0f * ray.direction, info.normal, n1, n2, r)) {
            r = reflection(-1.0f * ray.direction, info.normal);
          }
        } else {
          if (!refraction(-1.0f * ray.direction, -1.0f * info.normal, n1, n2,
                          r)) {
            r = reflection(-1.0f * ray.direction, -1.0f * info.normal);
          }
        }
        ray = Ray(info.position, r);
      } else {
        float AO = RTAO(scene, info, rng);
        Ray shadowray(info.position, Light);
        IntersectInfo shade;
        Vec3f matcolor = info.sphere->getColor();
        if (scene.hit(shadowray, shade)) {
          //衝突した場合（光源から見えない場合）
          col = matcolor * 0.1f * (1.0f - AO);
        } else {
          //衝突しない場合（光源からみえる）
          //入射方向ベクトル
          Vec3f wi = Light;
          float WdotN = std::max(dot(info.normal, wi), 0.0f);

          col = matcolor * Vec3f(WdotN) + matcolor * 0.1f * (1.0f - AO);
        }
        break;
      }
    } else {
      col = Vec3f(0.0);
    }
  }
  return col;
}

Vec3f Classical_RaytracerAO(const Ray &r, Scene &scene, RNGrandom &rng) {
  Ray ray = r;
  const int Max = 100;
  Vec3f Light = normalize(Vec3f(1.0, 1.0, 0.0));
  Vec3f col;

  IntersectInfo info;
  if (scene.hit(ray, info)) {
    float AO = RTAO(scene, info, rng);
    col = Vec3f(1.0f - AO);
  }
  return col;
}

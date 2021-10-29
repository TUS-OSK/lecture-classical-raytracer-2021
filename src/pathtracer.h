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
#define Pi 3.141592f

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

Vec3f SphereSampling(const float u, const float v, float &pdf) {
  float theta = std::acos(std::max(1.0f - u, 0.0f));
  float phi = 2.0f * Pi * v;
  pdf = 1.0f / (2.0f * Pi);
  return Vec3f(std::cos(phi) * std::sin(theta), std::cos(theta),
               std::sin(phi) * std::sin(theta));
}

Vec3f CosineSampling(const float u, const float v, float &pdf) {
  float theta = 0.5f * std::acos(std::clamp(1.0f - 2.0f * u, -1.0f, 1.0f));
  float phi = 2.0f * Pi * v;
  pdf = std::cos(theta) / Pi;
  return Vec3f(std::cos(phi) * std::sin(theta), std::cos(theta),
               std::sin(phi) * std::sin(theta));
}

Vec3f Lambert(Vec3f &wi, float &pdf, RNGrandom &rng, const Vec3f &rho) {
  wi = SphereSampling(rng.getRandom(), rng.getRandom(), pdf);
  Vec3f BSDF = rho / (float)Pi;
  return BSDF;
}

Vec3f Metallic(const Vec3f &wo, Vec3f &wi, float &pdf, const Vec3f &rho) {
  Vec3f n = Vec3f(0., 1., 0.);
  wi = reflection(wo, n);
  float cosine = std::abs(wi[1]);
  Vec3f BSDF = rho / cosine;
  pdf = 1;
  return BSDF;
}

float fresnel(const Vec3f &wo, const Vec3f &n, float ior1, float ior2) {
  float F0 = std::pow((ior1 - ior2) / (ior1 + ior2), 2.0);
  float F = F0 + (1.0 - F0) * std::pow(1.0f - dot(wo, n), 5.0);
  return F;
}
Vec3f glass(const Vec3f &wo, Vec3f &wi, float &pdf, const Vec3f &rho, float IOR,
            RNGrandom &rng) {
  Vec3f n(0, 1, 0);
  float ior1, ior2;
  //内部かどうかの判定
  //外側からの侵入
  if (wo[1] > 0) {
    ior1 = 1.0f;
    ior2 = IOR;
  }
  //内部から出る
  else {
    ior1 = IOR;
    ior2 = 1.0f;
    n = Vec3f(0, -1, 0);
  }

  const float Fr = fresnel(wo, n, ior1, ior2);
  //フレネル反射の場合
  if (Fr > rng.getRandom()) {
    wi = reflection(wo, n);
    pdf = 1.0;
    return rho / std::abs(wi[1]);
  }
  //屈折の場合
  else {
    Vec3f t;
    if (refraction(wo, n, ior1, ior2, t)) {
      //屈折した場合
      wi = t;
      pdf = 1;
      return rho / std::abs(wi[1]);
    } else {
      //全反射
      wi = reflection(wo, n);
      pdf = 1.0f;
      return rho / std::abs(wi[1]);
    }
  }
}

Vec3f Pathtracer(const Ray &r, Scene &scene, RNGrandom &rng) {
  Vec3f LTE = 0;
  Vec3f s = 1;
  Ray ray = r;

  float counter = 0;
  float p = 0.99;

  for (int i = 0; i < 100; i++) {
    IntersectInfo info;
    if (rng.getRandom() > 0.99) {
      break;
    }
    s = s / p;

    //空に当たった場合の処理
    if (!scene.hit(ray, info)) {
      LTE = s * 1.0f;
      break;
    }
    if (info.sphere->getMaterial() == Material::Emmition) {
      LTE = s * 2.0f * Vec3f(1.0, 1.0, 1.4);
      break;
    }
    //空に行かない場合

    //方向サンプリング
    //接空間の基底ベクトル
    Vec3f t, b;
    if (info.normal[1] < 0.9f) {
      t = normalize(cross(info.normal, Vec3f(0, 1, 0)));
    } else {
      t = normalize(cross(info.normal, Vec3f(0, 0, -1)));
    }
    b = normalize(cross(t, info.normal));

    Vec3f wi;
    Vec3f wo = WorldtoLocal(t, info.normal, b, -1.0f * ray.direction);
    float pdf;
    Vec3f bsdf;
    Vec3f rho = info.sphere->getColor();

    if (info.sphere->getMaterial() == Material::Diffuse) {
      bsdf = Lambert(wi, pdf, rng, rho);
    } else if (info.sphere->getMaterial() == Material::Mirror) {
      bsdf = Metallic(wo, wi, pdf, rho);
    } else if (info.sphere->getMaterial() == Material::Glass) {
      bsdf = glass(wo, wi, pdf, rho, 1.4, rng);
    }

    //ローカルからワールド方向へ
    Vec3f next_direction = LocaltoWorld(t, info.normal, b, wi);

    //次に飛ばすレイ
    ray = Ray(info.position + next_direction * 0.01f, next_direction);

    // throughputの計算
    float cosine = std::abs(dot(info.normal, next_direction));

    s = s * bsdf * cosine / pdf;
  }

  return LTE;
}

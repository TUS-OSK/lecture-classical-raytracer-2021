#include <omp.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>

#include "image.h"
#include "intersectinfo.h"
#include "pathtracer.h"
#include "pinhole.h"
#include "rng.h"
#include "scene.h"
#include "sphere.h"
#include "vec3.h"
using namespace std;
int main() {
  Image img(512, 512);
  unsigned int width = img.getWidth();
  unsigned int height = img.getHeight();
  unsigned int sampling = 10;
  PinholeCamera camera(Vec3f(4, 1, 7), normalize(-1.0f * Vec3f(4, 1, 7)));

  Scene scene;
  scene.addSphere(
      Sphere(Vec3f(-2, 0, 1), 1.0, Material::Diffuse, Vec3f(0.2, 0.2, 0.8)));
  scene.addSphere(
      Sphere(Vec3f(0), 1.0, Material::Diffuse, Vec3f(0.8, 0.2, 0.2)));
  scene.addSphere(
      Sphere(Vec3f(2, 0, -1), 1.0, Material::Diffuse, Vec3f(0.2, 0.8, 0.2)));
  scene.addSphere(Sphere(Vec3f(-2, 3, 1), 1.0, Material::Diffuse, Vec3f(0.9f)));
  scene.addSphere(Sphere(Vec3f(3, 1, 2), 1.0, Material::Diffuse, Vec3f(0.9f)));
  scene.addSphere(
      Sphere(Vec3f(0, -1001, 0), 1000, Material::Diffuse, Vec3f(0.9f)));

  Vec3f Light = normalize(Vec3f(-1, 1.0, 0));
  auto start = std::chrono::system_clock::now();
  std::cout << "Raytracing start" << std::endl;

#pragma omp parallel for schedule(dynamic, 1)
  for (int j = 0; j < img.getHeight(); ++j) {
    for (int i = 0; i < img.getWidth(); ++i) {
      Vec3f sampcol;
      RNGrandom rng(i + width * j);

      for (int k = 0; k < sampling; k++) {
        const float u = (2.0f * (i + rng.getRandom() - 0.5f) - width) / height;
        const float v = (2.0f * (j + rng.getRandom() - 0.5f) - height) / height;

        const Ray ray = camera.cameraRay(u, v);
        Vec3f col = Pathtracer(ray, scene, rng);
        sampcol = sampcol + col;
      }
      sampcol = sampcol / static_cast<float>(sampling);
      img.setPixel(i, j, sampcol);
    }
  }
  auto end = std::chrono::system_clock::now();
  std::cout << "End :"
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     start)
                   .count()
            << "ms" << std::endl;

  img.writePPM("sampling");

  return 0;
}
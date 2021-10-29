#pragma once

#include "vec3.h"

class Sphere;

struct IntersectInfo {
  //交差距離
  float distance;
  //交差位置
  Vec3f position;
  //法線ベクトル
  Vec3f normal;
  //スフィアのポインタ
  Sphere* sphere;
};

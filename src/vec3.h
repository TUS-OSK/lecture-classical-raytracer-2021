#ifndef _VEC3_H
#define _VEC3_H

#include <cmath>
#include <iostream>

template <typename T>
struct Vec3 {
  T v[3];

  Vec3() {
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
  }

  Vec3(T in) {
    v[0] = in;
    v[1] = in;
    v[2] = in;
  }

  Vec3(T x, T y, T z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
  }

  T operator[](unsigned int i) const { return v[i]; }
  T &operator[](unsigned int i) { return v[i]; }
};

//ベクトルの加算
template <typename T>
inline Vec3<T> operator+(const Vec3<T> &a, const Vec3<T> &b) {
  Vec3<T> ret;
  for (int i = 0; i < 3; ++i) {
    ret[i] = a[i] + b[i];
  }

  return ret;
}

//ベクトルの減算
template <typename T>
inline Vec3<T> operator-(const Vec3<T> &a, const Vec3<T> &b) {
  Vec3<T> ret;
  for (int i = 0; i < 3; ++i) {
    ret[i] = a[i] - b[i];
  }

  return ret;
}

// ベクトル * スカラー
template <typename T>
inline Vec3<T> operator*(const Vec3<T> &a, const T &s) {
  Vec3<T> ret;
  for (int i = 0; i < 3; i++) {
    ret[i] = a[i] * s;
  }
  return ret;
}

// スカラー * ベクトル
template <typename T>
inline Vec3<T> operator*(const T &s, const Vec3<T> &a) {
  Vec3<T> ret;
  for (int i = 0; i < 3; i++) {
    ret[i] = a[i] * s;
  }
  return ret;
}

// ベクトル / スカラー
template <typename T>
inline Vec3<T> operator/(const Vec3<T> &a, const T &s) {
  Vec3<T> ret;
  for (int i = 0; i < 3; i++) {
    ret[i] = a[i] / s;
  }
  return ret;
}

// スカラー / ベクトル
template <typename T>
inline Vec3<T> operator/(const T &s, const Vec3<T> &a) {
  Vec3<T> ret;
  for (int i = 0; i < 3; i++) {
    ret[i] = s / a[i];
  }
  return ret;
}

// アダマール積
template <typename T>
inline Vec3<T> operator*(const Vec3<T> &a, const Vec3<T> &b) {
  Vec3<T> ret;
  for (int i = 0; i < 3; i++) {
    ret[i] = a[i] * b[i];
  }
  return ret;
}

// ノルム
template <typename T>
inline float nolm(const Vec3<T> &vec) {
  float sum = 0;
  for (int i = 0; i < 3; i++) {
    sum += vec[i] * vec[i];
  }

  return std::sqrt(sum);
}
template <typename T>
inline float nolm2(const Vec3<T> &vec) {
  float no = nolm(vec);
  return no * no;
}

//　内積
template <typename T>
inline float dot(const Vec3<T> &a, const Vec3<T> &b) {
  float sum = 0;
  for (int i = 0; i < 3; ++i) {
    sum += a[i] * b[i];
  }
  return sum;
}

//　外積
template <typename T>
inline Vec3<T> cross(const Vec3<T> &a, const Vec3<T> &b) {
  Vec3<T> ret;
  ret[0] = a[1] * b[2] - a[2] * b[1];
  ret[1] = a[2] * b[0] - a[0] * b[2];
  ret[2] = a[0] * b[1] - a[1] * b[0];

  return ret;
}

//　正規化
template <typename T>
inline Vec3<T> normalize(const Vec3<T> &v) {
  return v / nolm(v);
}

//　出力
template <typename T>
inline std::ostream &operator<<(std::ostream &ost, const Vec3<T> &v) {
  ost << "(" << v[0] << "," << v[1] << "," << v[2] << ")";
  return ost;
}

using Vec3f = Vec3<float>;

inline Vec3f reflection(const Vec3f &v, const Vec3f &n) {
  return normalize(-1.0f * v + 2.0f * dot(v, n) * n);
}

inline bool refraction(const Vec3f &v, const Vec3f &n, const float n1,
                       const float n2, Vec3f &r) {
  Vec3f th = (-n1 / n2) * (v - dot(v, n) * n);

  if (nolm2(th) > 1.0) {
    return false;
  }

  const Vec3f tp = -std::sqrt(std::max(1.0f - nolm2(th), 0.0f)) * n;
  r = tp + th;
  return true;
}
#endif
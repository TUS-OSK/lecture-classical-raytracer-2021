#ifndef _RAY_H
#define _RAY_H
#include "vec3.h"
struct Ray
{
	Vec3f direction;
	Vec3f origin;
	float MAXLIM;
	float MINLIM;

	Ray(const Vec3f &origin, const Vec3f &direction) : origin(origin), direction(direction) {}
	Ray(const Vec3f &origin, const Vec3f &direction, float Max, float Min) : origin(origin), direction(direction), MAXLIM(Max), MINLIM(Min) {}

	Vec3f post(float t) { return origin + t * direction; }
};

#endif
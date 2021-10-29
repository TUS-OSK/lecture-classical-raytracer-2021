#pragma once

#include "vec3.h"
#include "ray.h"
#include <cmath>
class PinholeCamera
{
private:
	Vec3f camerapos;
	//カメラの直交座標
	Vec3f cf;
	Vec3f cr;
	Vec3f cu;

public:
	PinholeCamera(Vec3f pos, Vec3f atlook) : camerapos(pos), cf(atlook)
	{
		Vec3f n(0, 1, 0);
		if (std::abs(cf[1]) > 0.95)
		{
			n = Vec3f(0, 0, 1);
		}
		cr = normalize(cross(cf, n));
		cu = normalize(cross(cr, cf));
	}

	Ray cameraRay(float u, float v)
	{
		Vec3f Iij = camerapos + u * cr + v * cu;
		Vec3f Pin = camerapos + cf;
		Vec3f dir = normalize(Pin - Iij);

		return Ray(Iij, dir);
	}
};
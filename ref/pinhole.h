#ifndef _PINHOLE_H
#define _PINHOLE_H

#include "vec3.h"
#include "ray.h"
#include <iostream>

using vec3f = Vec3f;
class pincamera
{
private:
	vec3f camerapos;
	vec3f front;
	vec3f yoko;
	vec3f ue;
	vec3f pinhole;

public:
	pincamera(vec3f cp, vec3f f)
	{
		front = f;
		yoko = cross(f, vec3f(0, 1, 0));
		ue = cross(yoko, f);
		camerapos = cp;
		pinhole = cp + normalize(f);
		std::cout << camerapos << std::endl;
		std::cout << yoko << std::endl;
		std::cout << ue << std::endl;
		std::cout << pinhole << std::endl;
	}

	Ray getray(float i, float j)
	{
		vec3f imagepos = camerapos + i * yoko + j * ue;
		//std::cout << imagepos << std::endl;
		vec3f direction = pinhole - imagepos;
		Ray result(imagepos, normalize(direction));
		return result;
	}
};

#endif
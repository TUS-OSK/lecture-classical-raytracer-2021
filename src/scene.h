#pragma once

#include <vector>
#include "sphere.h"
#include "intersectinfo.h"
#include "ray.h"
class Scene
{
private:
	std::vector<Sphere> object;

public:
	Scene(const Sphere &s)
	{
		object.push_back(s);
	}

	Scene() {}

	void addSphere(const Sphere &s)
	{
		object.push_back(s);
	}

	bool hit(const Ray &ray, IntersectInfo &info)
	{
		bool result = false;
		info.distance = 10000.0;

		for (int i = 0; i < object.size(); i++)
		{
			IntersectInfo test;
			if (object[i].hit(ray, test))
			{
				if (info.distance > test.distance)
				{

					result = true;
					info = test;
				}
			}
		}

		return result;
	}
};
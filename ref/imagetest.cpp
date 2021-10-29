#include <iostream>
#include "./vec3.h"
#include "./image.h"
#include "pinhole.h"
using namespace std;
int main()
{
	const unsigned int width = 540 * 2;
	const unsigned int height = 540 * 2;

	pincamera camera(Vec3f(0.0f), Vec3f(0, 0, -1));
	Image img(width, height);
	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			float u, v;
			u = (2.0f * i - width) / height;
			v = (2.0f * j - height) / height;
			// cout << u << endl;
			// cout << v << endl;
			const Ray cameraray = camera.getray(u, v);
			//cout << "ray" << cameraray.direction;
			img.setPixel(i, j, 0.5f * (cameraray.direction + Vec3f(1.0)));
		}
	}

	img.writePNG("output");
	return 0;
}
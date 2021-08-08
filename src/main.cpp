#include <iostream>
#include "vec3.h"
#include "image.h"
using namespace std;
int main()
{

	Image img(512, 512);
	unsigned int width = img.getWidth();
	unsigned int height = img.getHeight();
	for (int j = 0; j < img.getHeight(); ++j)
	{
		for (int i = 0; i < img.getWidth(); ++i)
		{
			img.setPixel(i, j, Vec3f(static_cast<float>(i) / width, static_cast<float>(j) / height, 1.0f));
		}
	}

	img.writePPM("gamma");

	return 0;
}
#include "plot.h"
#include <iostream>
#include <cmath>
#include "vec3.h"

inline float g1(float x, float mue)
{
	return mue * x + 2.0 * (1.0 - mue) * x * x / (1.0 + x * x);
}

inline float g2(float x, float mue)
{
	return mue * x + (1.0 - mue) * x * x * std::exp((1.0f - x * x) / 4.0);
}

int main()
{
	unsigned int width = 512 * 2, height = 512 * 2;
	float xmin = -1e2, xmax = 1e2;
	float ymin = -1e2, ymax = 1e2;
	float lx = xmax - xmin;
	float ly = ymax - ymin;
	Vec3f RGB(1);

	Plot plt(width, height, xmin, xmax, ymin, ymax);
	double x = 1.0;
	double y = 1.0;
	double alpha = 0.001;
	double sigma = 0.00;
	double mue = -0.7770;
	for (int j = 0; j < 100; j++)
	{
		mue -= 0.001;
		for (int i = 0; i < 50000; i++)
		{
			double sx = y + alpha * y * (1.0f - sigma * y * y) + g2(x, mue);
			double sy = -x + g2(sx, mue);

			x = sx;
			y = sy;
			//std::cout << x << y << std::endl;
			float u = x / lx;
			float v = y / ly;
			float ds = i / 10000.0f - i / 10000;
			RGB = Vec3f(1.0);
			plt.setPlot(sx, sy, RGB);
		}
		std::string filename = "Gumowski_Mira_map_" + std::to_string(mue);
		plt.writePlot(filename);
		plt.reset();
		std::cout << filename + " comp" << std::endl;
	}
	return 0;
}

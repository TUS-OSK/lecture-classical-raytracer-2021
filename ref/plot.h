#ifndef _PLOT_H
#define _PLOT_H

#include "image.h"
#include <algorithm>
#include "vec3.h"
#include <string>
class Plot
{
private:
	Image *img;
	float plotx_min, plotx_max;
	float ploty_min, ploty_max;
	float plotwidth, plotheight;

public:
	Plot(unsigned int width, unsigned int height, float pxmin, float pxmax, float pymin, float pymax) : plotx_min(pxmin), plotx_max(pxmax), ploty_min(pymin), ploty_max(pymax)
	{
		img = new Image(width, height);

		plotwidth = plotx_max - plotx_min;
		plotheight = ploty_max - ploty_min;
	}

	~Plot()
	{
		delete img;
	}

	void setPlot(float x, float y, Vec3f &RGB)
	{
		if (x <= plotx_max && x >= plotx_min && y <= ploty_max && y >= ploty_min)
		{
			float disx = x - plotx_min;
			float disy = y - ploty_min;

			unsigned int xidx = static_cast<unsigned int>(img->getWidth() * disx / plotwidth);
			unsigned int yidx = static_cast<unsigned int>(img->getHeight() * disy / plotheight);

			img->setPixel(xidx, yidx, RGB);
		}
	}

	void writePlot(std::string file)
	{
		img->writePNG(file);
	}

	void reset()
	{
		img->reset();
	}
};
#endif
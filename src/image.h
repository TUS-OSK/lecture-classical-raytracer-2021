#ifndef _IMAGE_H
#define _IMAGE_H
#include <fstream>
#include "vec3.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
class Image
{
private:
	unsigned int Height;
	unsigned int Width;
	float *pixel;

public:
	Image(unsigned int width, unsigned int height) : Width(width), Height(height)
	{
		pixel = new float[Height * Width * 3];
		for (int j = 0; j < height; ++j)
		{
			for (int i = 0; i < width; ++i)
			{
				const unsigned int idx = i * 3 + j * width * 3;
				pixel[idx] = 0;
				pixel[idx + 1] = 0;
				pixel[idx + 2] = 0;
			}
		}
	}

	~Image()
	{
		delete[] pixel;
	}

	unsigned int getWidth() { return Width; }
	unsigned int getHeight() { return Height; }
	void setPixel(unsigned int u, unsigned int v, const Vec3f &RGB)
	{
		const unsigned int idx = u * 3 + v * 3 * Width;
		pixel[idx] = RGB[0];
		pixel[idx + 1] = RGB[1];
		pixel[idx + 2] = RGB[2];
	}

	void writePPM(std::string filename)
	{
		std::ofstream file(filename + ".ppm");
		if (!file)
		{
			std::cerr << "failed" << std::endl;
		}

		file << "P3" << std::endl;
		file << Width << " " << Height << std::endl;
		file << "255" << std::endl;

		this->gamma();
		for (int j = 0; j < Height; ++j)
		{
			for (int i = 0; i < Width; ++i)
			{
				const int idx = 3 * i + 3 * j * Width;
				unsigned int R = static_cast<unsigned int>(std::clamp(255 * pixel[idx], 0.0f, 255.0f));
				unsigned int G = static_cast<unsigned int>(std::clamp(255 * pixel[idx + 1], 0.0f, 255.0f));
				unsigned int B = static_cast<unsigned int>(std::clamp(255 * pixel[idx + 2], 0.0f, 255.0f));

				file << R << " " << G << " " << B << " " << std::endl;
			}
		}
		file.close();
		std::string cmd = "convert " + filename + ".ppm " + filename + ".png";
		system(cmd.c_str());
	}

	void gamma()
	{
		for (int j = 0; j < Height; ++j)
		{
			for (int i = 0; i < Width; ++i)
			{
				const unsigned int idx = i * 3 + j * 3 * Width;

				pixel[idx] = std::pow(pixel[idx], 1.0f / 2.2f);
				pixel[idx + 1] = std::pow(pixel[idx + 1], 1.0f / 2.2f);
				pixel[idx + 2] = std::pow(pixel[idx + 2], 1.0f / 2.2f);
			}
		}
	}
};
#endif
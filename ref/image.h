#ifndef _IMAGE_H
#define _IMAGE_H

#include <fstream>
#include <string>
#include <algorithm>

#include "vec3.h"
class Image
{
private:
	float *pixel;
	unsigned int width;
	unsigned int height;

public:
	Image(unsigned int width, unsigned int height) : width(width), height(height)
	{
		pixel = new float[width * height * 3];

		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				const int idx = i * 3 + 3 * width * j;
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

	unsigned int getWidth() const { return width; }
	unsigned int getHeight() const { return height; }

	void setPixel(unsigned int i, unsigned int j, const Vec3f &RGB)
	{
		unsigned int idx = i * 3 + 3 * width * j;
		pixel[idx] = RGB[0];
		pixel[idx + 1] = RGB[1];
		pixel[idx + 2] = RGB[2];
	}

	void writePNG(const std::string &filename)
	{
		std::ofstream file(filename + ".ppm");
		if (!file)
		{
			std::cerr << "failed to open" << filename << std::endl;
		}

		this->gammaCorrection();

		file << "P3" << std::endl;
		file << width << " " << height << std::endl;
		file << "255" << std::endl;

		for (int j = 0; j < height; ++j)
		{
			for (int i = 0; i < width; ++i)
			{
				const int idx = 3 * i + 3 * width * j;
				float R = pixel[idx];
				float G = pixel[idx + 1];
				float B = pixel[idx + 2];

				file << static_cast<unsigned int>(std::clamp(255.0f * R, 0.0f, 255.0f)) << " ";
				file << static_cast<unsigned int>(std::clamp(255.0f * G, 0.0f, 255.0f)) << " ";
				file << static_cast<unsigned int>(std::clamp(255.0f * B, 0.0f, 255.0f)) << std::endl;
			}
		}

		file.close();
		std::string cmd = "convert " + filename + ".ppm " + filename + ".png";
		system(cmd.c_str());
	}
	//ガンマ補正
	void gammaCorrection()
	{
		for (int j = 0; j < height; ++j)
		{
			for (int i = 0; i < width; ++i)
			{
				const int idx = 3 * i + 3 * width * j;
				pixel[idx] = std::pow(pixel[idx], 1 / 2.2f);
				pixel[idx + 1] = std::pow(pixel[idx + 1], 1 / 2.2f);
				pixel[idx + 2] = std::pow(pixel[idx + 2], 1 / 2.2f);
			}
		}
	}

	void reset()
	{
		for (int j = 0; j < height; ++j)
		{
			for (int i = 0; i < width; ++i)
			{
				const int idx = 3 * i + 3 * width * j;
				pixel[idx] = 0;
				pixel[idx + 1] = 0;
				pixel[idx + 2] = 0;
			}
		}
	}
};
#endif
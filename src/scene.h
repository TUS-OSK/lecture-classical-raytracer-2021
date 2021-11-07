#pragma once
#define TINYOBJLOADER_IMPLEMENTATION

#include "external/tinyobjloader/tiny_obj_loader.h"
#include <vector>
#include "sphere.h"
#include "intersectinfo.h"
#include "ray.h"
#include "shape.h"
#include <memory>
#include <iostream>
#include "triangle.h"

bool loadObj(const std::string &filepath,std::vector<float> &vertex,std::vector<unsigned int> &index){
	tinyobj::ObjReader reader;
	if(!reader.ParseFromFile(filepath)){

		if(!reader.Error().empty()){
			std::cerr << reader.Error();	
		}

		return false;
	}

	if(!reader.Warning().empty()){
		std::cout << reader.Warning();
	}

	const auto &attrib = reader.GetAttrib();
	const auto &shapes = reader.GetShapes();

	vertex = attrib.vertices;

	for(size_t s = 0; s < shapes.size(); ++s){
		for(const auto &idx: shapes[s].mesh.indices){
			index.push_back(idx.vertex_index);
		}
	}

	return true;
}

class Scene
{
private:
	std::vector<std::shared_ptr<Shape>> object;

public:
	Scene(const std::shared_ptr<Shape> &s)
	{
		object.push_back(s);
	}

	Scene() {}

	void addShape(const std::shared_ptr<Shape> &s)
	{
		object.push_back(s);
	}

	void addPolygon(const std::string& filepath,const Material mat,const Vec3f color){
		std::vector<float> vertex;
		std::vector<unsigned int> index;

		loadObj(filepath,vertex,index);

		int nface = index.size() /3;
		for(int i = 0; i < nface; i++){
			Vec3f p[3];
			for(int k = 0; k < 3; k++){
				unsigned int idx = index[i*3 + k] * 3;
				p[k] = Vec3(vertex[idx],vertex[idx+1],vertex[idx+2]);
			}

			object.push_back(std::make_shared<Triangle>(p[0],p[1],p[2],mat,color));
		}
	}

	bool hit(const Ray &ray, IntersectInfo &info)
	{
		bool result = false;
		info.distance = 10000.0;

		for (int i = 0; i < object.size(); i++)
		{
			IntersectInfo test;
			if (object[i]->hit(ray, test))
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


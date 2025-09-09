#pragma once
#include "Model.h"
#include "ResourceManager.h"

class Sphere : public Model
{
public:
	Sphere(float radius);
	Sphere(float radius, bool wireframe);
	Sphere(float radius, const char* tex);
};


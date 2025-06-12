#pragma once
#include "Object.h"
#include "ResourceManager.h"

class Sphere : public Object
{
public:
	Sphere(float radius);
	Sphere(float radius, bool wireframe);
	Sphere(float radius, const char* tex);
};


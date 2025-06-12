#pragma once
#include "Object.h"
#include "ResourceManager.h"
#include "Constants.h"
#include <functional>

class Planet : public Object
{
	float rotationScaler;
	float translationScaler;

public:
	Planet(float radius, const char* tex, float r, float t);
	void draw() override;
};


#pragma once
#include "Model.h"

class Corp : public Model
{
	float rotationScaler;
	float translationScaler;

public:
	Corp(float radius, const char* tex, float r, float t);
	Corp(float radius, const char* tex, float r, float t, const char* program);
	void draw() override;
};


#pragma once
#include "Model.h"

class Corp : public Model
{
	float rotationScaler;
	float translationScaler;

public:
	Corp(MaterialData &mat, float radius, float r, float t);
	Corp(MaterialData &mat, float radius, float r, float t, const char* program);
	void draw() override;
};


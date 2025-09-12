#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Model.h"

typedef std::vector<glm::vec3> Positions;

class Instances
{
	Model* obj;
	Positions Pos;
public:
	Instances(Model* obj, Positions pos);
	void setInstances(Positions inst);
	void drawInstances();
};


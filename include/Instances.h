#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Object.h"

typedef std::vector<glm::vec3> Positions;

class Instances
{
	Object* obj;
	Positions Pos;
public:
	Instances(Object* obj, Positions pos);
	void setInstances(std::vector<glm::vec3> inst);
	void drawInstances();
};


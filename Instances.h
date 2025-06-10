#pragma once
#include "Object.h"
#include <GLM/glm.hpp>
#include <vector>

typedef std::vector<glm::vec3> Positions;

class Instances
{
	Object& Obj;
	Positions& Pos;
public:
	Instances(Object& obj, Positions& pos);
	void setInstances(std::vector<glm::vec3> inst);
	void drawInstances();
};


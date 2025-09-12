#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "Model.h"

class Instances
{
	std::unique_ptr<Model> obj;
	std::vector<glm::vec3>  Pos{};
public:
	Instances(std::unique_ptr<Model>obj, glm::vec3 pos);
	void setInstances(std::vector<glm::vec3> inst);
	void addInstances(std::vector<glm::vec3> inst);
	void deleteInstances(int index);
	void drawInstances();
};


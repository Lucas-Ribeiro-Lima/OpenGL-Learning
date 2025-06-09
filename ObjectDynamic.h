#pragma once
#include "Object.h"
#include <GLM/glm.hpp>

class ObjectDynamic : public Object
{
	std::function<float(void)> rotationUpdater = nullptr;
	std::function<glm::vec3(void)> translateUpdater = nullptr;
	std::function<glm::vec3(void)> scaleUpdater = nullptr;

public:
	using Object::Object;
	void draw() override;
	void setRotate(std::function<float(void)> rotationUpdater, glm::vec3 axis);
	void setTranslate(std::function<glm::vec3(void)> fn);
	void setScale(std::function<glm::vec3(void)> fn);
};


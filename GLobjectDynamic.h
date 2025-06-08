#pragma once
#include "GLobject.h"
#include <GLM/glm.hpp>

class GLobjectDynamic : public GLobject
{
	std::function<float(void)> rotationUpdater = nullptr;
	std::function<glm::vec3(void)> translateUpdater = nullptr;
	std::function<glm::vec3(void)> scaleUpdater = nullptr;

public:
	using GLobject::GLobject;
	void draw() override;
	void setRotate(std::function<float(void)> rotationUpdater, glm::vec3 axis);
	void setTranslate(std::function<glm::vec3(void)> fn);
	void setScale(std::function<glm::vec3(void)> fn);
};


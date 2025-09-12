#pragma once

#include <glm/glm.hpp>
#include "Program.h"
#include "Mesh.h"
#include "Texture.h"

using uint = unsigned int;

class Model
{
protected:
	glm::vec3 translateAxis = glm::vec3(0.0f);
	glm::vec3 scaleAxis = glm::vec3(1.0f); 
	glm::vec3 rotateAxis = glm::vec3(1.0f);

	Program* PROG = nullptr;
	Mesh* GEO = nullptr;
	Texture* TEX = nullptr;

	uint VAO = 0;
	float rotateDeg = 0;

	bool wireframe = false;
	   
	void saveBuffer();
	void genVertexArrayBuffer();
	void bindGeometry();
	void bindTexture();

public:
	Model(Mesh* geometry, Program* Program);
	Model(Mesh* geometry, Texture* texture, Program* Program);
	uint getID() const;
	Model& setProgram(Program* Program);
	Model& setTranslate(glm::vec3 axis);
	Model& setRotate(float deg, glm::vec3 axis);
	Model& setScale(glm::vec3 axis);
	void setWireframe(bool state);
	virtual void draw();
};


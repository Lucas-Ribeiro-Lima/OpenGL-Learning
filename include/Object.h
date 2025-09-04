#pragma once
#include <glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "Program.h"
#include "Geometry.h"
#include "Texture.h"

class Object
{
protected:
	glm::vec3 translateAxis = glm::vec3(0.0f);
	glm::vec3 scaleAxis = glm::vec3(1.0f); 
	glm::vec3 rotateAxis = glm::vec3(1.0f);

	Program* PROG = nullptr;
	Geometry* GEO = nullptr;
	Texture* TEX = nullptr;

	GLuint VAO = 0;
	GLfloat rotateDeg = 0;

	bool wireframe = 0;
	   
	void saveBuffer();
	void genVertexArrayBuffer();
	void bindGeometry();
	void bindTexture();

public:
	Object(Geometry* geometry, Program* Program);
	Object(Geometry* geometry, Texture* texture, Program* Program);
	GLuint getID() const;
	Object& setProgram(Program* Program);
	Object& setTranslate(glm::vec3 axis);
	Object& setRotate(float deg, glm::vec3 axis);
	Object& setScale(glm::vec3 axis);
	void setWireframe(bool state);
	virtual void draw();
};


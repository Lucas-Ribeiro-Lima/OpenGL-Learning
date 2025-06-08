#pragma once
#include <glad/glad.h>
#include <functional>
#include <GLM/glm.hpp>
#include <vector>
#include "Program.h"

class GLobject
{
protected:
	glm::vec3 translateAxis = glm::vec3(0.0f);
	glm::vec3 scaleAxis = glm::vec3(1.0f); 
	glm::vec3 rotateAxis = glm::vec3(1.0f);

	Program& PROG;

	size_t verticesSize = 0;
	size_t indicesSize = 0;

	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;
	GLuint TEX = 0;
	float rotateDeg = 0;
	   
	void saveBuffer();
	void genVertexArrayBuffer();
	void genVertexBufferObject(std::vector<float>& vertices);
	void genElementBufferObject(std::vector<GLuint>& indices);
	void genTextureBuffer(const char* texture);

public:
	GLobject(std::vector<float>& vertices, std::vector<GLuint>& indices, Program& Program);
	GLobject(std::vector<float>& vertices, std::vector<GLuint>& indices, const char* texture, Program& Program);
	~GLobject();
	GLuint getID() const;
	void setProgram(Program& Program);
	void setTranslate(glm::vec3 axis);
	void setRotate(float deg, glm::vec3 axis);
	void setScale(glm::vec3 axis);
	virtual void draw();
};


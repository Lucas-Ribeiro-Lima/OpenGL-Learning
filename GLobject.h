#pragma once
#include <glad/glad.h>
#include <vector>
#include "Program.h"

class GLobject
{
private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint ProgramID;
	unsigned int verticesSize;
	unsigned int indicesSize;

	GLobject(std::vector<float>& vertices);
	void saveBuffer();

public:
	GLobject(std::vector<float>& vertices, std::vector<GLuint>& indices);
	GLobject(std::vector<float>& vertices, std::vector<GLuint>& indices, Program& Program);
	~GLobject();
	GLuint getID();
	GLuint getProgramID();
	void setProgram(Program& Program);
	void draw();
};


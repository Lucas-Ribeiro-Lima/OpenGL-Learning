#pragma once
#include <glad/glad.h>
#include <vector>
#include "Program.h"

class GLobject
{
private:
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;
	GLuint ProgramID = 0;
	unsigned int verticesSize = 0;
	unsigned int indicesSize = 0;

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


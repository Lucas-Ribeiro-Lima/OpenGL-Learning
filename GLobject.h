#pragma once
#include <glad/glad.h>

class GLobject
{
private:
	GLuint VAO;
	GLuint VBO;

public:
	GLobject();
	~GLobject();
	GLuint getId();
};


#pragma once
#include <glad/glad.h>

class Shader
{	
protected:
	char infoLog[512];
	const char* shaderSource;
	GLuint ID;
	int sucess;

public:
	GLuint getId();
	void errors();
};


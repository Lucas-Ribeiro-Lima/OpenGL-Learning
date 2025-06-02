#pragma once
#include <glad/glad.h>
#include <string>

class Shader
{	
protected:
	char infoLog[512];
	std::string shaderSource;
	GLuint ID;
	int sucess;

public:
	GLuint getId();
	void errors();
};


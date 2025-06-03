#pragma once
#include <glad/glad.h>
#include "FragmentShader.h"
#include "VertexShader.h"

class Program
{
private:
	char infoLog[512];
	int sucess;
	GLuint ID;
public:
	Program(const char* shaderSrc, const char* fragmentSrc);
	~Program();
	GLuint getId();
	void errors();
};


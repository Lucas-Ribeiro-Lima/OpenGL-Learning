#pragma once
#include <glad/glad.h>
#include "FragmentShader.h"
#include "VertexShader.h"
#include <string>

class Program
{
private:
	char infoLog[512] = {};
	int sucess = 0;
	GLuint ID  = 0;
public:
	Program(const char shaderSrc[], const char fragmentSrc[]);
	~Program();
	GLuint getId();
	void errors();
};


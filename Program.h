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
	void setUniform1I(const char name[], GLint value) const;
	void setUniform1UI(const char name[], GLuint value) const;
	void setUniform1f(const char name[], GLfloat value) const;
	void setUniform3f(const char name[], GLfloat value[3]) const;
	void use();
	void errors();
};


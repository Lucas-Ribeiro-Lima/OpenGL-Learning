#pragma once
#include <glad/glad.h>
#include "FragmentShader.h"
#include "VertexShader.h"
#include <string>

class Program
{
private:
	char infoLog[512];
	int sucess;
	GLuint ID;
public:
	Program(std::string& shaderSrc, std::string& fragmentSrc);
	~Program();
	GLuint getId();
	void errors();
};


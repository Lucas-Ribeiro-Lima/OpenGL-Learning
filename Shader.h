#pragma once
#include <glad/glad.h>
#include <iostream>
#include "Utils.h"

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


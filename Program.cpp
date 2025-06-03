#include "Program.h"
#include "FragmentShader.h"
#include "VertexShader.h"
#include <iostream>

Program::Program(std::string& shaderSrc, std::string& fragmentSrc) {
	const char* shaderptr = shaderSrc.c_str();
	const char* fragmentptr = fragmentSrc.c_str();

	VertexShader shader(shaderptr);
	FragmentShader fragment(fragmentptr);

	ID = glCreateProgram();
	GLuint shaderId = shader.getId();
	GLuint fragmentId = fragment.getId();

	glAttachShader(ID, shaderId);
	glAttachShader(ID, fragmentId);
	glLinkProgram(ID);

	int sucess;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &sucess);

	if (!sucess) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(shaderId);
	glDeleteShader(fragmentId);
}

Program::~Program() {
	glDeleteProgram(ID);
}

void Program::errors() {
	glGetProgramiv(ID, GL_LINK_STATUS, &sucess);

	if (!sucess) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

GLuint Program::getId() {
	return ID;
}
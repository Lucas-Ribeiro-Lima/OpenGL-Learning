#include "Program.h"
#include "FragmentShader.h"
#include "VertexShader.h"
#include "Utils.h"
#include <iostream>

Program::Program(const char shaderSrc[], const char fragmentSrc[]) {

	VertexShader shader(Utils::readFile(shaderSrc).c_str());
	FragmentShader fragment(Utils::readFile(fragmentSrc).c_str());

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

void Program::use() {
	glUseProgram(ID);
}

void Program::setUniform1I(const char name[], GLint value) const {
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void Program::setUniform1f(const char name[], GLfloat value) const {
	glUniform1f(glGetUniformLocation(ID, name), value);
}
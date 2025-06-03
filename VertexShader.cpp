#include "VertexShader.h"
#include <iostream>

VertexShader::VertexShader(const char* source) {
	shaderSource = source;
	ID = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(ID, 1, &shaderSource, NULL);
	glCompileShader(ID);

	int sucess;
	char infoLog[512];

	glGetShaderiv(ID, GL_COMPILE_STATUS, &sucess);

	if (!sucess) {
		glGetShaderInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

GLuint VertexShader::getId() {
	return ID;
}
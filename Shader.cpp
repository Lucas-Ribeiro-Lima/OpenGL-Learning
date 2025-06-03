#include <iostream>
#include "Shader.h"

void Shader::errors() {
	glGetShaderiv(ID, GL_COMPILE_STATUS, &sucess);

	if (!sucess) {
		glGetShaderInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

GLuint Shader::getId() {
	return ID;
}
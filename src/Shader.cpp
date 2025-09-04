#include "Shader.h"

void Shader::errors() {
	glGetShaderiv(ID, GL_COMPILE_STATUS, &sucess);

	if (!sucess) {
		glGetShaderInfoLog(ID, 512, NULL, infoLog);
		Utils::logger(std::format("ERROR::SHADER::VERTEX::COMPILATION_FAILED + {}", infoLog).c_str());
	}
}

GLuint Shader::getId() {
	return ID;
}
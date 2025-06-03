#include "FragmentShader.h"

FragmentShader::FragmentShader(const char* source) {
	shaderSource = source;
	ID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(ID, 1, &shaderSource, 0);
	glCompileShader(ID);
}

GLuint FragmentShader::getId() {
	return ID;
}
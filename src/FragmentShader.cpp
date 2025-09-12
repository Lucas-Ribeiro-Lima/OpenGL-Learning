#include "FragmentShader.h"
#include <glad.h>

FragmentShader::FragmentShader(const char* source) {
	ID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(ID, 1, &source, 0);
	glCompileShader(ID);

	Shader::errors();
}
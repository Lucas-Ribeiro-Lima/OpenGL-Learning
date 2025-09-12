#include "VertexShader.h"
#include <glad.h>

VertexShader::VertexShader(const char* source) {
	ID = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(ID, 1, &source, NULL);
	glCompileShader(ID);

	Shader::errors();
}

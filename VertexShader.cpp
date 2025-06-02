#include "VertexShader.h"
#include <glad/glad.h>
#include <string>

VertexShader::VertexShader(const std::string& source) {
	shaderSource = source;
	ID = glCreateShader(GL_VERTEX_SHADER);
}
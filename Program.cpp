#include "Program.h"

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
	setUniform4fv("transform", tMat4);
}

Program& Program::resetT() {
	tMat4 = glm::mat4(1.0f);
	return *this;
}

Program& Program::scale(glm::vec3 scaleProps) {
	tMat4 = glm::scale(tMat4, scaleProps);
	return *this;
};

Program& Program::rotate(float degree, glm::vec3 rotateProps) {
	tMat4 = glm::rotate(tMat4, degree, rotateProps);
	return *this;
};

Program& Program::translate(glm::vec3 translateProps) {
	tMat4 = glm::translate(tMat4, translateProps);
	return *this;
}

void Program::setUniform1I(const char name[], GLint value) const {
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void Program::setUniform1f(const char name[], GLfloat value) const {
	glUniform1f(glGetUniformLocation(ID, name), value);
}

void Program::setUniform4fv(const char name[], glm::mat4& mat) {
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(mat));
}
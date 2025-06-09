#include "Program.h"

Program::Program(const char* vertex, const char* fragment) {
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	VertexShader vShader(vertex);
	FragmentShader fShader(fragment);

	ID = glCreateProgram();
	GLuint shaderId = vShader.getId();
	GLuint fragmentId = fShader.getId();

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
	setUniform4fv("model", model);
	setUniform4fv("view", view);
	setUniform4fv("projection", projection);
}

Program& Program::resetT() {
	model = glm::mat4(1.0f);
	return *this;
}

Program& Program::scale(glm::vec3 scaleProps) {
	model = glm::scale(model, scaleProps);
	return *this;
};

Program& Program::rotate(float degree, glm::vec3 rotateProps) {
	model = glm::rotate(model, glm::radians(degree), rotateProps);
	return *this;
};

Program& Program::translate(glm::vec3 translateProps) {
	model = glm::translate(model, translateProps);
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
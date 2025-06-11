#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "FragmentShader.h"
#include "VertexShader.h"
#include "Utils.h"

class Program
{
private:
	char infoLog[512] = {};
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection;
	int sucess = 0;
	GLuint ID  = 0;

public:
	Program(const char* vertex, const char* fragment);
	~Program();
	Program& resetT();
	Program& scale(glm::vec3 scaleProps);
	Program& rotate(float degree, glm::vec3 rotateProps);
	Program& translate(glm::vec3 translateProps);
	void setUniform1I(const char name[], GLint value) const;
	void setUniform1UI(const char name[], GLuint value) const;
	void setUniform1f(const char name[], GLfloat value) const;
	void setUniform3f(const char name[], GLfloat value[3]) const;
	void setUniform4fv(const char name[], glm::mat4& mat);
	void use();
	void errors();
};

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "WindowGl.h"
#include <iostream>


//VBO Generation
void generateVBO();
//VAO Generation
unsigned int generateVAO();

//Shaders and program compilation
unsigned int shaderCompilation();
unsigned int fragmentCompilation();
unsigned int  programCompilation(unsigned int shader, unsigned int fragment);


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

int main() {

	WindowGl window = WindowGl(800, 600);

	if (window.hasErrors()) return -1;

	unsigned int VAO = generateVAO();
	generateVBO();

	unsigned int vertexShader = shaderCompilation();
	unsigned int fragmentShader = fragmentCompilation();

	unsigned int shaderProgram = programCompilation(vertexShader, fragmentShader);

	window.render(VAO, shaderProgram);

	glfwTerminate();
	return 0;

}

void generateVBO() {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

unsigned int generateVAO() {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	return VAO;
}


unsigned int shaderCompilation() {
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int sucess;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);

	if (!sucess) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return vertexShader;
}


unsigned int fragmentCompilation() {
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	return fragmentShader;
}


unsigned int  programCompilation(unsigned int shader, unsigned int fragment) {
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, shader);
	glAttachShader(shaderProgram, fragment);
	glLinkProgram(shaderProgram);

	int sucess;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess);

	if (!sucess) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(shader);
	glDeleteShader(fragment);
	return shaderProgram;
}




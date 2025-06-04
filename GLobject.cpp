#include "GLobject.h"
#include "Utils.h"
#include <iostream>
#include <GLFW/glfw3.h>

const int colorSystem[4] = { GL_RED, NULL, GL_RGB, GL_RGBA };

GLobject::GLobject(std::vector<float>& vertices, std::vector<GLuint>& indices, Program& program): PROG(program) {
	genVertexArrayBuffer();

	genVertexBufferObject(vertices);

	genElementBufferObject(indices);

	saveBuffer();
}

GLobject::GLobject(std::vector<float>& vertices, std::vector<GLuint>& indices, const char* texture, Program& program)
: PROG(program) {
	genVertexArrayBuffer();

	genVertexBufferObject(vertices);

	genElementBufferObject(indices);

	genTextureBuffer(texture);

	saveBuffer();
}

void GLobject::genVertexArrayBuffer() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void GLobject::genVertexBufferObject(std::vector<float>& vertices) {
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	verticesSize = vertices.size();
	glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

void GLobject::genElementBufferObject(std::vector<GLuint>& indices) {
	indicesSize = indices.size();

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void GLobject::genTextureBuffer(const char* path) {
	int width, heigth, nrChannels;
	unsigned char* data = Utils::loadTexture(path, width, heigth, nrChannels);



	glGenTextures(1, &TEX);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TEX);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, colorSystem[nrChannels - 1], width, heigth, 0, colorSystem[nrChannels - 1], GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}

	Utils::freeTexture(data);
}


void GLobject::setProgram(Program& program) {
	PROG = program;
}


void GLobject::saveBuffer() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}


GLobject::~GLobject() {
	if (glIsBuffer(VBO)) {
		glDeleteBuffers(1, &VBO);
	}
	if (glIsVertexArray(VAO)) {
		glDeleteVertexArrays(1, &VAO);
	}
	if (glIsBuffer(EBO)) {
		glDeleteBuffers(1, &EBO);
	}
	if (glIsTexture(TEX)) {
		glDeleteTextures(1, &TEX);
	}
}

void GLobject::draw() {
	PROG.use();

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
}


GLuint GLobject::getID() {
	return VAO;
}
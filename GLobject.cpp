#include "GLobject.h"
#include <GLFW/glfw3.h>


GLobject::GLobject(std::vector<float>& vertices) {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	verticesSize = vertices.size();
	glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

GLobject::GLobject(std::vector<float>& vertices, std::vector<GLuint>& indices)
	: GLobject::GLobject(vertices) {

	indicesSize = indices.size();

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	saveBuffer();
}


GLobject::GLobject(std::vector<float>& vertices, std::vector<GLuint>& indices, Program& program)
	: GLobject::GLobject(vertices, indices) {
	ProgramID = program.getId();
}


GLuint GLobject::getProgramID() {
	return ProgramID;
};

void GLobject::setProgram(Program& program) {
	ProgramID = program.getId();
}

void GLobject::saveBuffer() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);
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
}

void GLobject::draw() {
	glUseProgram(ProgramID);
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
}


GLuint GLobject::getID() {
	return VAO;
}
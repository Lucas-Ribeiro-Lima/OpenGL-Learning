#include "GLobject.h"


GLobject::GLobject() {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);	
}

GLobject::~GLobject() {
	if (glIsBuffer(VBO)) {
		glDeleteBuffers(1, &VBO);
	}
	if (glIsVertexArray(VAO)) {
		glDeleteVertexArrays(1, &VAO);
	}
}


GLuint GLobject::getId() {
	return VAO;
}
#include "Geometry.h"

Geometry::Geometry(std::vector<GLfloat>& vertexes, std::vector<GLuint>& indexes) {
	genVertexBufferObject(vertexes);
	genElementBufferObject(indexes);
}

void Geometry::genVertexBufferObject(std::vector<float>& vertexes) {
	vertexesSize = vertexes.size();

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexesSize * sizeof(float), vertexes.data(), GL_STATIC_DRAW);
}

void Geometry::genElementBufferObject(std::vector<GLuint>& indexes) {
	indexesSize = indexes.size();

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexesSize * sizeof(GLuint), indexes.data(), GL_STATIC_DRAW);
}

GLuint Geometry::getVBO() const {
	return VBO;
}

GLuint Geometry::getEBO() const {
	return EBO;
}

unsigned int Geometry::getVertexSize() const {
	return vertexesSize;
}

unsigned int Geometry::getIndexSize() const {
	return indexesSize;
}
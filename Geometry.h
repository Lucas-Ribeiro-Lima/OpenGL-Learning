#pragma once
#include <glad/glad.h>
#include <vector>

class Geometry
{
private:
	unsigned int vertexesSize = 0;
	unsigned int indexesSize = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;

public:
	Geometry(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	GLuint getVBO() const;
	GLuint getEBO() const;
	unsigned int getVertexSize() const;
	unsigned int getIndexSize() const;
	void genVertexBufferObject(std::vector<GLfloat>& vertices);
	void genElementBufferObject(std::vector<GLuint>& indices);
};
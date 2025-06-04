#pragma once
#include <glad/glad.h>
#include <vector>
#include "Program.h"

class GLobject
{
private:
	Program& PROG;
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;
	GLuint TEX = 0;
	size_t verticesSize = 0;
	size_t indicesSize = 0;

	void saveBuffer();
	void genVertexArrayBuffer();
	void genVertexBufferObject(std::vector<float>& vertices);
	void genElementBufferObject(std::vector<GLuint>& indices);
	void genTextureBuffer(const char* texture);
public:
	GLobject(std::vector<float>& vertices, std::vector<GLuint>& indices, Program& Program);
	GLobject(std::vector<float>& vertices, std::vector<GLuint>& indices, const char* texture, Program& Program);
	~GLobject();
	GLuint getID();
	void setProgram(Program& Program);
	void draw();
};


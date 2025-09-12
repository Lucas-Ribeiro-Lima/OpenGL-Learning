#include "Model.h"
#include <glad.h>

Model::Model(Mesh* geometry, Program* program): GEO(geometry), PROG(program) {
	genVertexArrayBuffer();

	bindGeometry();

	saveBuffer();
}

Model::Model(Mesh* geometry, Texture* texture, Program* program)
	: GEO(geometry), TEX(texture), PROG(program)
{
	genVertexArrayBuffer();

	bindGeometry();
	bindTexture();

	saveBuffer();
}

void Model::genVertexArrayBuffer()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void Model::bindGeometry()
{
	glBindBuffer(GL_ARRAY_BUFFER, GEO->getVBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GEO->getEBO());
}

void Model::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, TEX->getTex());
}

Model& Model::setProgram(Program* program)
{
	PROG = program;
	return *this;
}

void Model::saveBuffer()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

//Set a new translation transformation vetor for the object.
Model& Model::setTranslate(glm::vec3 axis)
{
	translateAxis = axis;
	return *this;
}

Model& Model::setRotate(float deg, glm::vec3 axis)
{
	rotateDeg = deg;
	rotateAxis = axis;
	return *this;
}

//Set a new scaling transformation vetor for the object.
Model& Model::setScale(glm::vec3 axis)
{
	scaleAxis = axis;
	return *this;
}

/*
	Draw function is called every frame in the main loop,
	applying the transformations of the object.
*/
void Model::draw()
{
	if (wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	(*PROG)
		.resetT()
		.translate(translateAxis)
		.rotate(rotateDeg, rotateAxis)
		.scale(scaleAxis)
		.use();

	if (TEX) {
		glBindTexture(GL_TEXTURE_2D, TEX->getTex());
	}

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, GEO->getIndexSize(), GL_UNSIGNED_INT, 0);
}

void Model::setWireframe(bool state) {
	wireframe = state;
}

GLuint Model::getID() const {
	return VAO;
}
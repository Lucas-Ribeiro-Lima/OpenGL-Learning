#include "Object.h"

Object::Object(Geometry* geometry, Program* program): GEO(geometry), PROG(program) {
	genVertexArrayBuffer();

	bindGeometry();

	saveBuffer();
}

Object::Object(Geometry* geometry, Texture* texture, Program* program)
: GEO(geometry), TEX(texture), PROG(program) {
	genVertexArrayBuffer();

	bindGeometry();
	bindTexture();

	saveBuffer();
}

void Object::genVertexArrayBuffer() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void Object::bindGeometry() {
	glBindBuffer(GL_ARRAY_BUFFER, GEO->getVBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GEO->getEBO());
}

void Object::bindTexture() {
	glBindTexture(GL_TEXTURE_2D, TEX->getTex());
}

Object& Object::setProgram(Program* program) {
	PROG = program;
	return *this;
}

void Object::saveBuffer() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

//Set a new translation transformation vetor for the object.
Object& Object::setTranslate(glm::vec3 axis) {
	translateAxis = axis;
	return *this;
}

Object& Object::setRotate(float deg, glm::vec3 axis) {
	rotateDeg = deg;
	rotateAxis = axis;
	return *this;
}

//Set a new scaling transformation vetor for the object.
Object& Object::setScale(glm::vec3 axis) {
	scaleAxis = axis;
	return *this;
}

/*
	Draw function is called every frame in the main loop,
	applying the transformations of the object.
*/
void Object::draw() {
	if (wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
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

void Object::setWireframe(bool state) {
	wireframe = state;
}

GLuint Object::getID() const {
	return VAO;
}
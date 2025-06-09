#include "Object.h"

Object::Object(Geometry& geometry, Program& program): GEO(geometry), TEX(nullptr), PROG(program) {
	genVertexArrayBuffer();

	bindGeometry();

	saveBuffer();
}

Object::Object(Geometry& geometry, Texture* texture, Program& program)
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
	glBindBuffer(GL_ARRAY_BUFFER, GEO.getVBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GEO.getEBO());
}

void Object::bindTexture() {
	glBindTexture(GL_TEXTURE_2D, TEX->getTex());
}

void Object::setProgram(Program& program) {
	PROG = program;
}

void Object::saveBuffer() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}


Object::~Object() {
	if (glIsVertexArray(VAO)) {
		glDeleteVertexArrays(1, &VAO);
	}
}

//Set a new translation transformation vetor for the object.
void Object::setTranslate(glm::vec3 axis) {
	translateAxis = axis;
}

void Object::setRotate(float deg, glm::vec3 axis) {
	rotateDeg = deg;
	rotateAxis = axis;
}

//Set a new scaling transformation vetor for the object.
void Object::setScale(glm::vec3 axis) {
	scaleAxis = axis;
}

/*
	Draw function is called every frame in the main loop,
	applying the transformations of the object.
*/
void Object::draw() {
	PROG
		.resetT()
		.translate(translateAxis)
		.rotate(rotateDeg, rotateAxis)
		.scale(scaleAxis)
		.use();

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, GEO.getIndexSize(), GL_UNSIGNED_INT, 0);
}


GLuint Object::getID() const {
	return VAO;
}
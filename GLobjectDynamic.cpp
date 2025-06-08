#include "GLobjectDynamic.h"

void GLobjectDynamic::setRotate(std::function<float(void)> fn, glm::vec3 axis) {
	rotationUpdater = fn;
	rotateAxis = axis;
}

void GLobjectDynamic::setScale(std::function<glm::vec3(void)> fn) {
	scaleUpdater = fn;
}

void GLobjectDynamic::setTranslate(std::function<glm::vec3(void)> fn) {
	translateUpdater = fn;
}

void GLobjectDynamic::draw() {
	if (rotationUpdater) {
		rotateDeg = rotationUpdater();
	}

	if (scaleUpdater) {
		scaleAxis = scaleUpdater();
	}
	
	if (translateUpdater) {
		translateAxis = translateUpdater();
	}


	GLobject::draw();
}
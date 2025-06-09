#include "ObjectDynamic.h"

void ObjectDynamic::setRotate(std::function<float(void)> fn, glm::vec3 axis) {
	rotationUpdater = fn;
	rotateAxis = axis;
}

void ObjectDynamic::setScale(std::function<glm::vec3(void)> fn) {
	scaleUpdater = fn;
}

void ObjectDynamic::setTranslate(std::function<glm::vec3(void)> fn) {
	translateUpdater = fn;
}

void ObjectDynamic::draw() {
	if (rotationUpdater) {
		rotateDeg = rotationUpdater();
	}

	if (scaleUpdater) {
		scaleAxis = scaleUpdater();
	}
	
	if (translateUpdater) {
		translateAxis = translateUpdater();
	}


	Object::draw();
}
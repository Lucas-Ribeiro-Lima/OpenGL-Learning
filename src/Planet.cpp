#include "Planet.h"
Planet::Planet(
	float radius,
	const char* tex,
	float r,
	float t
) : Object(
	getSphereGeometry(radius),
	getTexture(tex),
	getProgram(Constants::FRAG_1)
), rotationScaler(r), translationScaler(t) {}


void Planet::draw() {
	float time = glfwGetTime();

	glm::vec3 orbit{
		cos(time * translationScaler),
		0.0f,
		sin(time * translationScaler)
	};

	translateAxis *= orbit;
	rotateAxis += glm::vec3(0, 1, 0);
	rotateDeg = glm::mod(time * rotationScaler, 360.0f);

	Object::draw();
}
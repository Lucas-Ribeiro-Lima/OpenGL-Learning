#include "Corp.h"
Corp::Corp(
	float radius,
	const char* tex,
	float r,
	float t
) : Model(
	getSphereData(radius),
	getTextureData(tex),
	getProgram(Constants::FRAG_1)
), rotationScaler(r), translationScaler(t) {}

Corp::Corp(
	float radius,
	const char* tex,
	float r,
	float t,
	const char* program
) : Model(
	getSphereData(radius),
	getTextureData(tex),
	getProgram(program)
), rotationScaler(r), translationScaler(t) {}

void Corp::draw() {
	float time = glfwGetTime();

	glm::vec3 orbit{
		cos(time * translationScaler),
		0.0f,
		sin(time * translationScaler)
	};

	translateAxis *= orbit;
	rotateAxis += glm::vec3(0, 1, 0);
	rotateDeg = glm::mod(time * rotationScaler, 360.0f);

	Model::draw();
}
#include "Corp.h"
#include "GLFW/glfw3.h"
#include "ResourceManager.h"
#include "Constants.h"

Corp::Corp(
	MaterialData &mat,
	float radius,
	float r,
	float t
) : Model(
	getSphereData(radius),
	getProgram(Constants::FRAG_1),
	mat
), rotationScaler(r), translationScaler(t) {}

Corp::Corp(
	MaterialData &mat,
	float radius,
	float r,
	float t,
	const char* program
) : Model(
	getSphereData(radius),
	getProgram(program),
	mat
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
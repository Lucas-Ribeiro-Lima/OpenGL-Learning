#include "WindowGl.h"
#include "Cube.h"
#include "Sphere.h"
#include "Camera.h"
#include "ResourceManager.h"
#include <vector>

std::vector<glm::vec3> cubePositions = {
	glm::vec3(4.0f,  2.0f, -10.0f),
	glm::vec3(-4.0f, -3.0f, -6.0f),
	glm::vec3(0.0f,  6.0f, -20.0f),
	glm::vec3(-5.0f, 1.0f, -8.0f),
	glm::vec3(3.0f, -1.0f, -5.0f),
	glm::vec3(5.0f,  3.5f, -15.0f),
	glm::vec3(-2.5f, 2.2f, -4.5f),
	glm::vec3(2.5f, -2.5f, -11.0f),
	glm::vec3(-3.5f, 0.5f, -3.0f),
	glm::vec3(0.5f,  1.0f, -13.0f)
};

std::vector<glm::vec3> spherePositions = {
	glm::vec3(1.0f,  1.0f, -3.0f),
	glm::vec3(-2.0f, 2.0f, -8.0f),
	glm::vec3(0.0f, -1.5f, -6.0f),
	glm::vec3(3.5f, -0.5f, -10.0f),
	glm::vec3(-3.5f, 1.2f, -4.0f),
	glm::vec3(2.2f,  2.5f, -7.0f),
	glm::vec3(-1.0f, -2.0f, -9.5f),
	glm::vec3(1.8f, -1.2f, -5.0f),
	glm::vec3(-4.2f, 0.8f, -12.0f),
	glm::vec3(0.7f,  0.3f, -2.0f)
};

std::vector<glm::vec3> pos{
	glm::vec3( 0.0f, 0.0f,  0.0f),
};

float DELTA_TIME = 0.0f;

int main() {
	WindowGl window(800, 600, DELTA_TIME, &getCamera());

	if (window.hasErrors()) return -1;

	Sphere sphere{ 1.0f };
	Instances sphereInstances{ sphere, pos };

	std::vector<Instances*> data{ &sphereInstances };

	window.render(data);

	return 0;
}





#include "WindowGl.h"
#include "Cube.h"
#include "Sphere.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "Utils.h"
#include <vector>

constexpr unsigned int WIDTH = 800;
constexpr unsigned int HEIGHT = 600;

int main() {
	std::vector<glm::vec3> positions;
	Utils::genPlanetsOrbit(positions);

	WindowGl window(WIDTH, HEIGHT, &getCamera());

	if (window.hasErrors()) return -1;

	Sphere sphere{ 1.0f };

	Instances sphereInstances{ sphere, positions };

	std::vector<Instances*> data{ &sphereInstances };

	window.render(data);

	return 0;
}





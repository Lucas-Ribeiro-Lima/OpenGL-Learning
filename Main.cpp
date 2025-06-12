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

struct Corp {
    float radius;
    const char* tex;
    glm::vec3 position;
};

std::vector<Corp> planets{
    { 20.0f, "assets/sun.jpg",     glm::vec3(0.0f, 0.0f, 0.0f) },   // Sun
    { 12.0f, "assets/jupiter.jpg", glm::vec3(60.0f, 0.0f, 0.0f) },  // Jupiter
    {  6.0f, "assets/mars.jpg",    glm::vec3(40.0f, 0.0f, 0.0f) },  // Mars
    {  3.0f, "assets/mercury.jpg", glm::vec3(15.0f, 0.0f, 0.0f) },  // Mercury
    { 11.0f, "assets/saturn.jpg",  glm::vec3(80.0f, 0.0f, 0.0f) },  // Saturn
    {  5.0f, "assets/venus.jpg",   glm::vec3(25.0f, 0.0f, 0.0f) },  // Venus
    {  6.5f, "assets/earth.jpg",   glm::vec3(30.0f, 0.0f, 0.0f) },  // Earth
};

int main() {
	WindowGl window(WIDTH, HEIGHT, &getCamera());

	if (window.hasErrors()) return -1;

    std::vector<Instances> data;

    for (int i = 0; i < planets.size(); i++) {
        Sphere* planet = new Sphere{ planets[i].radius, planets[i].tex };
        std::vector<glm::vec3> instances{ planets[i].position };
        data.push_back(Instances{ planet, instances });
    }

	window.render(data);

	return 0;
}





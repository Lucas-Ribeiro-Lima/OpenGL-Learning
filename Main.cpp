#include "WindowGl.h"
#include "Camera.h"
#include "Planet.h"
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
    float rotateScaler;
    float translateScaler;
};

std::vector<Corp> planets{
    { 20.0f, "assets/sun.jpg",     glm::vec3( 0.0f,   0.0f,   0.0f),     0.0f,  0.0f },   // Sun
    {  2.0f, "assets/mercury.jpg", glm::vec3(-30.0f,  0.0f, -30.0f),     5.0f,  4.8f },   // Mercury
    {  3.0f, "assets/venus.jpg",   glm::vec3( 45.0f,  0.0f,  45.0f),     3.0f,  3.5f },   // Venus
    {  3.3f, "assets/earth.jpg",   glm::vec3(-60.0f,  0.0f, -60.0f),    8.0f,  3.0f },   // Earth
    {  2.5f, "assets/mars.jpg",    glm::vec3( 75.0f,  0.0f,  75.0f),    7.0f,  2.4f },   // Mars
    { 12.0f, "assets/jupiter.jpg", glm::vec3(-110.0f, 0.0f, -110.0f),   12.0f,  1.3f },   // Jupiter
    { 10.0f, "assets/saturn.jpg",  glm::vec3( 150.0f, 0.0f,  150.0f),   10.0f,  1.0f },   // Saturn
    {  4.5f, "assets/uranus.jpg",  glm::vec3(-190.0f, 0.0f, -190.0f),    6.0f,  0.8f },   // Uranus
    {  4.0f, "assets/neptune.jpg", glm::vec3( 230.0f, 0.0f,  230.0f),    5.0f,  0.5f },   // Neptune
};

int main() {
	WindowGl window(WIDTH, HEIGHT, &getCamera());

	if (window.hasErrors()) return -1;

    std::vector<Instances> data;

    for (int i = 0; i < planets.size(); i++) {
        Planet* planet = new Planet{ 
            planets[i].radius, 
            planets[i].tex, 
            planets[i].rotateScaler, 
            planets[i].translateScaler
        };

        std::vector<glm::vec3> instances{ planets[i].position };
        data.push_back(Instances{ planet, instances });
    }

	window.render(data);

	return 0;
}





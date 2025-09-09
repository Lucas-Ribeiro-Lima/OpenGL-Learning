#include "WindowGl.h"
#include "Camera.h"
#include "Corp.h"
#include "ResourceManager.h"
#include "Config.h"
#include <vector>

#include "Star.h"

constexpr unsigned int WIDTH = 800;
constexpr unsigned int HEIGHT = 600;

struct CorpData {
    const char* tex;
    glm::vec3 position;
    float radius;
    float rotateScaler;
    float translateScaler;
};

std::vector<CorpData> planets{
            { ASSETS_DIR "mercury.jpg", glm::vec3(-30.0f,  0.0f, -30.0f),      2.0f,  5.0f,  0.8f },   // Mercury
            { ASSETS_DIR "venus.jpg",   glm::vec3( 45.0f,  0.0f,  45.0f),      3.0f,  3.0f,  0.5f },   // Venus
            { ASSETS_DIR "earth.jpg",   glm::vec3(-60.0f,  0.0f, -60.0f),      3.3f,  8.0f,  0.2f },   // Earth
            { ASSETS_DIR "mars.jpg",    glm::vec3( 75.0f,  0.0f,  75.0f),      2.5f,  7.0f,  0.1f },   // Mars
            { ASSETS_DIR "jupiter.jpg", glm::vec3(-110.0f, 0.0f, -110.0f),    12.0f, 12.0f,  0.3f },   // Jupiter
            { ASSETS_DIR "saturn.jpg",  glm::vec3( 150.0f, 0.0f,  150.0f),    10.0f, 10.0f,  0.4f },   // Saturn
            { ASSETS_DIR "uranus.jpg",  glm::vec3(-190.0f, 0.0f, -190.0f),     4.5f,  6.0f,  0.8f },   // Uranus
            { ASSETS_DIR "neptune.jpg", glm::vec3( 230.0f, 0.0f,  230.0f),     4.0f,  5.0f,  0.1f },   // Neptune
    };

int main() {
	WindowGl window(WIDTH, HEIGHT, &getCamera());

	if (window.hasErrors()) return -1;

    std::vector<Instances> data;

    for (int i = 0; i < planets.size(); i++) {
        Corp* planet = new Corp{
            planets[i].radius, 
            planets[i].tex, 
            planets[i].rotateScaler, 
            planets[i].translateScaler,

        };

        std::vector<glm::vec3> instances{ planets[i].position };
        data.push_back(Instances{ planet, instances });
    }

    Star* sun = new Star{ 20.0f, ASSETS_DIR "sun.jpg", 1.0f,  0.0f };
    Instances starsInstances{ sun, std::vector<glm::vec3>{glm::vec3{0.0f}  } };

    data.push_back(starsInstances);

	window.render(data);

	return 0;
}





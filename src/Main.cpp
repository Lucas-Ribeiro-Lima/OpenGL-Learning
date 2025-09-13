#include "Window.h"
#include "Camera.h"
#include "Material.h"
#include "Corp.h"
#include "ResourceManager.h"
#include "Config.h"
#include <vector>

#include "Star.h"

struct CorpData {
    MaterialData material;
    glm::vec3 position;
    float radius;
    float rotateScaler;
    float translateScaler;
};

std::vector<CorpData> planets{
    {MaterialData{ASSETS_DIR "mercury.jpg"}, glm::vec3(-30.0f, 0.0f, -30.0f), 2.0f, 5.0f, 0.8f}, // Mercury
    {MaterialData{ASSETS_DIR "venus.jpg"}, glm::vec3(45.0f, 0.0f, 45.0f), 3.0f, 3.0f, 0.5f}, // Venus
    {
        MaterialData{ASSETS_DIR "earth.jpg", ASSETS_DIR "earth_specular_map.tif", ASSETS_DIR "earth_nightmap.jpg"},
        glm::vec3(-60.0f, 0.0f, -60.0f), 3.3f, 8.0f, 0.2f
    }, // Earth
    {MaterialData{ASSETS_DIR "mars.jpg"}, glm::vec3(75.0f, 0.0f, 75.0f), 2.5f, 7.0f, 0.1f}, // Mars
    {MaterialData{ASSETS_DIR "jupiter.jpg"}, glm::vec3(-110.0f, 0.0f, -110.0f), 12.0f, 12.0f, 0.3f}, // Jupiter
    {MaterialData{ASSETS_DIR "saturn.jpg"}, glm::vec3(150.0f, 0.0f, 150.0f), 10.0f, 10.0f, 0.4f}, // Saturn
    {MaterialData{ASSETS_DIR "uranus.jpg"}, glm::vec3(-190.0f, 0.0f, -190.0f), 4.5f, 6.0f, 0.8f}, // Uranus
    {MaterialData{ASSETS_DIR "neptune.jpg"}, glm::vec3(230.0f, 0.0f, 230.0f), 4.0f, 5.0f, 0.1f}, // Neptune
};

int main() {
    Window window{};

    if (window.hasErrors()) return -1;

    std::vector<Instances> data;

    for (int i = 0; i < planets.size(); i++) {
        std::unique_ptr<Model> planet_ptr = std::make_unique<Corp>(
            planets[i].material,
            planets[i].radius,
            planets[i].rotateScaler,
            planets[i].translateScaler);

        data.emplace_back(std::move(planet_ptr), planets[i].position);
    }

    std::unique_ptr<Model> sun_ptr = std::make_unique<Star>(MaterialData{ASSETS_DIR "sun.jpg"}, 20.0f, 1.0f, 0.0f);
    data.emplace_back(std::move(sun_ptr), glm::vec3{0.0f});

    window.render(data);

    return 0;
}

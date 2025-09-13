#include "Window.h"
#include "Camera.h"
#include "Material.h"
#include "Corp.h"
#include "ResourceManager.h"
#include "Config.h"

#include <vector>

struct CorpData {
    MaterialData material;
    glm::vec3 position;
    float radius;
    float rotateScaler;
    float translateScaler;
};

std::vector<CorpData> planets{
    {{ASSETS_DIR "mercury.jpg"}, {-30.0f, 0.0f, -30.0f}, 2.0f, 5.0f, 0.8f}, // Mercury
    {{ASSETS_DIR "venus.jpg"}, {45.0f, 0.0f, 45.0f}, 3.0f, 3.0f, 0.5f}, // Venus
    {
        {ASSETS_DIR "earth.jpg", ASSETS_DIR "earth_specular_map.tif", ASSETS_DIR "earth_nightmap.jpg"},
        {-60.0f, 0.0f, -60.0f}, 3.3f, 8.0f, 0.2f
    }, // Earth
    {{ASSETS_DIR "mars.jpg"}, {75.0f, 0.0f, 75.0f}, 2.5f, 7.0f, 0.1f}, // Mars
    {{ASSETS_DIR "jupiter.jpg"}, {-110.0f, 0.0f, -110.0f}, 12.0f, 12.0f, 0.3f}, // Jupiter
    {{ASSETS_DIR "saturn.jpg"}, {150.0f, 0.0f, 150.0f}, 10.0f, 10.0f, 0.4f}, // Saturn
    {{ASSETS_DIR "uranus.jpg"}, {-190.0f, 0.0f, -190.0f}, 4.5f, 6.0f, 0.8f}, // Uranus
    {{ASSETS_DIR "neptune.jpg"}, {230.0f, 0.0f, 230.0f}, 4.0f, 5.0f, 0.1f}, // Neptune
};

std::vector<CorpData> stars{
    {
        {ASSETS_DIR "sun.jpg"}, {0.0f, 0.0f, 0.0f}, 20.0f, 0.1f, 0.0f
    }
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

    for (int i = 0; i < stars.size(); i++) {
        std::unique_ptr<Model> sun_ptr = std::make_unique<Corp>(
            stars[i].material,
            stars[i].radius,
            stars[i].rotateScaler,
            stars[i].translateScaler,
            Constants::FRAG_LIGHT);
        data.emplace_back(std::move(sun_ptr), stars[i].position);
    }

    window.render(data);

    return 0;
}

#include <Light.h>

namespace oriongl::core {

bool Lighting::hasDirectional() const { return directional.has_value(); }

graphics::DirectionalLight &Lighting::getDirectionalLight() { return directional.value(); };

std::vector<graphics::PointLight> &Lighting::getPointLights() { return points; };

graphics::LightScale &Lighting::getLightScaling() { return lightScale; };

size_t Lighting::addPointLight(graphics::PointLight light) {
    points.push_back(light);
    return points.size() - 1;
};

size_t Lighting::addPointLight(glm::vec3 position, graphics::LightColor color) {
    graphics::PointLight light{position, color};
    points.push_back(light);

    return points.size() - 1;
}

void Lighting::removePointLight(size_t idx) { points.erase(points.begin() + idx); };
} // namespace oriongl::core

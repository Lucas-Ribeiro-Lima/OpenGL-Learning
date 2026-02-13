//
// Created by lucas.lima on 10/09/2025.
//

#ifndef OPENGL_LEARNING_LIGHT_H
#define OPENGL_LEARNING_LIGHT_H

#include "glm/vec3.hpp"
#include "optional"

namespace oriongl::graphics {

struct LightScale {
    float ambient = 0.05f;
    float diffuse = 0.8f;
    float specular = 1.0f;
};

struct LightAttenuation {
    float constant = 1.0f;
    float linear = 0.0014f;
    float quadratic = 0.000007f;
};

struct Light {
    std::array<float, 3> _color{0.0f, 0.0f, 0.0f};
};

struct DirectionalLight : Light {
    glm::vec3 _direction{0.0f, 0.0f, 0.0f};
};

struct PointLight : Light {
    glm::vec3 _position;
    LightAttenuation _attenuation;

    PointLight(glm::vec3 pos, std::array<float, 3> color = {0.0f, 0.0f, 0.0f}) : _position(pos), Light(color) {}
};

struct SpotLight : Light {
    glm::vec3 _position;
    glm::vec3 _direction;
    float cutOff;
};

} // namespace oriongl::graphics

namespace oriongl::core {
class Lighting {
    std::optional<graphics::DirectionalLight> directional = std::nullopt;
    std::vector<graphics::PointLight> points;
    std::vector<graphics::SpotLight> spotlights;
    graphics::LightScale lightScale;

  public:
    Lighting() = default;
    Lighting(std::vector<graphics::PointLight> &lights) : points(lights) {};
    Lighting(graphics::DirectionalLight dir_light, std::vector<graphics::PointLight> &lights)
        : points(lights), directional(dir_light) {};

    bool hasDirectional() const;
    void setDirectional(glm::vec3 light);

    size_t addPointLight(glm::vec3 position);
    size_t addPointLight(graphics::PointLight light);
    void removePointLight(size_t idx);

    graphics::DirectionalLight &getDirectionalLight();
    std::vector<graphics::PointLight> &getPointLights();
    graphics::LightScale &getLightScaling();
};

} // namespace oriongl::core

#endif // OPENGL_LEARNING_LIGHT_H

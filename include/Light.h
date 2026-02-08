//
// Created by lucas.lima on 10/09/2025.
//

#ifndef OPENGL_LEARNING_LIGHT_H
#define OPENGL_LEARNING_LIGHT_H

#include "glm/vec3.hpp"

namespace oriongl::graphics {

struct LightScale {
    float ambient = 0.05f;
    float diffuse = 0.8f;
    float specular = 1.0f;
};

struct Light {
    std::array<float, 3> _color;
    LightScale _scaling;
};

struct DirectionalLight : Light {
    glm::vec3 _direction{0.0f, -0.45f, -0.45f};
};

struct PointLight : Light {
    glm::vec3 _position;
};

struct SpotLight : Light {
    glm::vec3 _position;
    glm::vec3 _direction;
    float cutOff;
};

struct Lighting {
    graphics::DirectionalLight directional;
    std::vector<graphics::PointLight> points;
    std::vector<graphics::SpotLight> spotlights;
};

} // namespace oriongl::graphics

#endif // OPENGL_LEARNING_LIGHT_H

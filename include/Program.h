#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Camera.h"
#include "Light.h"
#include "Shader.h"

namespace oriongl::graphics {
class Program {
    glm::mat4 model = glm::mat4(1.0f);
    unsigned int ID = 0;

  public:
    Program(std::shared_ptr<Shader> vertex, std::shared_ptr<Shader> fragment);

    Program &scale(glm::vec3 scaleProps);

    Program &rotate(float degree, glm::vec3 rotateProps);

    Program &translate(glm::vec3 translateProps);

    void resetModelMatrix();

    void setModelMatrix();

    void setLight(Light &light);

    void setCamera(core::Camera &camera);

    void setTextures();

    void setUniform1I(const char name[], int value) const;

    void setUniform1UI(const char name[], int value) const;

    void setUniform1f(const char name[], float value) const;

    void setUniform3fv(const char name[], glm::vec3 &vec);

    void setUniform4fv(const char name[], glm::mat4 &mat);

    void setUniform1i(const char name[], int value);

    void use();

    unsigned int getId();

    void errors();
};
} // namespace oriongl::graphics

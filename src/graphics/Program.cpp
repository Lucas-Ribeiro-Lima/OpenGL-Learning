#include "Program.h"
#include "Shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad.h>

namespace oriongl::graphics {
Program::Program(std::shared_ptr<Shader> vertex, std::shared_ptr<Shader> fragment) {
    ID = glCreateProgram();
    glAttachShader(ID, vertex->getId());
    glAttachShader(ID, fragment->getId());
    glLinkProgram(ID);

    errors();
}

void Program::errors() {
    int success = 0;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        glDeleteProgram(ID);
        throw std::runtime_error{infoLog};
    }
}

void Program::use() { glUseProgram(ID); }

unsigned int Program::getId() { return ID; }

void Program::resetModelMatrix() { model = glm::mat4(1.0f); }

void Program::setModelMatrix() { setUniform4fm("model", model); }

Program &Program::scale(glm::vec3 scaleProps) {
    model = glm::scale(model, scaleProps);
    return *this;
};

Program &Program::rotate(float degree, glm::vec3 rotateProps) {
    model = glm::rotate(model, glm::radians(degree), rotateProps);
    return *this;
};

Program &Program::translate(glm::vec3 translateProps) {
    model = glm::translate(model, translateProps);
    return *this;
}

void Program::setCamera(core::Camera &camera) {
    setUniform4fm("view", camera.getView());
    setUniform3fv("viewPos", camera.getViewPosition());
    setUniform4fm("projection", camera.getPerspective());
}

// Shader light structure
// struct LightScaling {
//  float ambient;
//  float diffuse;
//  float specular;
//}
// struct Light {
//   vec4 position; position.w set to 0.0f when directional.
//   vec4 direction; direction.w set to 0.0f when point light.
//   vec3 color; default to white.
//   float cutOff; 0.0f when not spotlight.
// }
void Program::setLights(graphics::Lighting &lights) {
    auto &_direction = lights.directional._direction;
    auto &_color = lights.directional._color;
    auto &_scaling = lights.directional._scaling;

    setUniform4fv("directional.position", glm::vec4(0.0f));
    setUniform4fv("directional.direction", glm::vec4{_direction, 0.0f});
    setUniform3fv("directional.color", glm::vec3(_color[0], _color[1], _color[2]));
    setUniform1f("directional.cutOff", 0.0f);

    setUniform1f("lightScaling.ambient", _scaling.ambient);
    setUniform1f("lightScaling.diffuse", _scaling.diffuse);
    setUniform1f("lightScaling.specular", _scaling.specular);
}

void Program::setTextures() {
    // Texture
    setUniform1i("material.diffuse", 0);
    setUniform1i("material.specular", 1);
    setUniform1i("material.emission", 2);
    setUniform1f("material.shininess", 1.0f);
}

void Program::setUniform1I(const char name[], GLint value) const { glUniform1i(glGetUniformLocation(ID, name), value); }

void Program::setUniform1f(const char name[], GLfloat value) const { glUniform1f(glGetUniformLocation(ID, name), value); }

void Program::setUniform3fv(const char name[], glm::vec3 vec) {
    glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(vec));
}

void Program::setUniform4fv(const char name[], glm::vec4 vec) {
    glUniform4fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(vec));
}

void Program::setUniform4fm(const char name[], glm::mat4 mat) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Program::setUniform1i(const char name[], GLint value) { glUniform1i(glGetUniformLocation(ID, name), value); }
} // namespace oriongl::graphics

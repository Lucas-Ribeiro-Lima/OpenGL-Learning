//
// Created by lucas.lima on 10/09/2025.
//

#ifndef OPENGL_LEARNING_MATERIAL_H
#define OPENGL_LEARNING_MATERIAL_H
#include "glm/vec3.hpp"
#include "Texture.h"

class Material {
  public:
    glm::vec3 ambient{1.0f};
    glm::vec3 diffuse{1.0f};
    glm::vec3 specular{1.0f};
};

#endif //OPENGL_LEARNING_MATERIAL_H
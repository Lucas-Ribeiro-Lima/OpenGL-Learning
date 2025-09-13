//
// Created by lucas.lima on 10/09/2025.
//

#ifndef OPENGL_LEARNING_MATERIAL_H
#define OPENGL_LEARNING_MATERIAL_H

#include "Texture.h"
#include "Constants.h"
#include <memory>

struct MaterialData {
    const char *diffusePath = Constants::TEXTURE_BLACK_FALLBACK;
    const char *specularPath = Constants::TEXTURE_BLACK_FALLBACK;
    const char *emissivePath = Constants::TEXTURE_BLACK_FALLBACK;
};

class Material {
    std::shared_ptr<Texture> diffuse;
    std::shared_ptr<Texture> specular;
    std::shared_ptr<Texture> emissive;
    float shininess = 1.0f;
  public:
    Material();
    Material(MaterialData &mat);
    void bindMaterial();
};

#endif //OPENGL_LEARNING_MATERIAL_H
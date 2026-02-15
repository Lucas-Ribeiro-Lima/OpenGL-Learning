//
// Created by lucas.lima on 10/09/2025.
//

#ifndef OPENGL_LEARNING_MATERIAL_H
#define OPENGL_LEARNING_MATERIAL_H

#include "Program.h"
#include "Texture.h"

#include <array>
#include <memory>
#include <vector>

namespace oriongl::graphics {

typedef std::array<float, 3> MaterialColor;

class Material {
    std::vector<std::shared_ptr<Texture>> textures;
    MaterialColor _color = {1.0f, 1.0f, 1.0f};

  public:
    Material();
    void loadTexture(std::shared_ptr<Texture> texture);
    void bindMaterial(std::shared_ptr<Program> prg);
    void setColor(MaterialColor color);
};
} // namespace oriongl::graphics

#endif // OPENGL_LEARNING_MATERIAL_H
